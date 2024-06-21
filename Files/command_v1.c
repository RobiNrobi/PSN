#include "command_v1.h"
#include "fvec_man.h"
#include "tmp_utils.h"
#include "utility.h"
#include <stdio.h>
#include <unistd.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/*
** From man execve:
** int execve( const char *pathname
**             , char *const _Nullable argv[]
**             , char *const _Nullable envp[]);
** --> execve() executes the program referred to by pathname.
** --> pathname must be either a binary executable, or a script starting with a
**              line of the form: #!interpreter [optional-arg]
** --> argv is an array of pointers to strings passed to the new program as its
**          command-line arguments. By convention, the first of these strings
**          (i.e., argv[0]) should contain the filename associated with the file
**          being executed. The argv array must be terminated by a NULL pointer.
**          (Thus, in the new program, argv[argc] will be NULL.)
** --> envp is an array of pointers to strings, conventionally of the form
**          key=value, which are passed as the environment of the new program.
**          The envp array must be terminated by a NULL pointer.
** [...]
** By default, file descriptors remain open across an execve() [...].
** [...]
** On success, execve() does not return, on error -1 is returned, and errno is
** set to indicate the error.
*/
int execute_command(const char *name, char * const argl[], char * const envp[])
{
	fprintf( tracciato, "execute_command(%s, char**, char**)\n", name );
	t_vec	path;
	int		i;
	char	*cmd;
	char	*tmp;

	fvec_init(&path, 0);
	expand_path(&path);
	i = 0;
	while (path.size > i)
	{

		tmp = my_strjoin(path.tstr[i].s, "/");
		cmd = my_strjoin(tmp, name);
		free(tmp);
		if (!access(cmd, X_OK))
			if (-1 == execve(cmd, argl, envp))
				perror(cmd);
		free(cmd);
		++i;
	}
	fvec_destroy(&path);
	return (1);
}
void take_commands(t_vec *cmd, char **envp)
{
	int i;
	int j;
	int len;
	char **args;

	i = 0;
	while (cmd->size > i)
	{
		if (is_redirect(cmd->tstr[i]))
			i++;
		else if (cmd->tstr[i].state == word)
			len++;
		i++;		
	}
	args = (char **)malloc(len * sizeof(char *) + 1);
	i = 0;
	j = 0;
	while (cmd->size > i)
	{
		if (is_redirect(cmd->tstr[i]))
			i++;
		else if (cmd->tstr[i].state == word)
		{
			args[j] = my_strdup(cmd->tstr[i].s);
			j++;
		}
		i++;
	}
	args[j] = NULL;
	execute_command(args[0], args, envp);
}

char	*my_strdup(const char *str)
{
	int		nume;
	char	*cpy;

	nume = my_strlen(str) + 1;
	cpy = (char *)malloc(nume * sizeof(char));
	if (!cpy)
	{
		free(cpy);
		return (NULL);
	}
	my_memcpy(cpy, str, nume);
	return ((char *)cpy);
}

void	*my_memcpy(void *dest, const void *src, int n)
{
	int			i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
