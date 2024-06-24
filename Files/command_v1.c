#include "command_v1.h"
#include "fvec_man.h"
#include "tmp_utils.h"
#include "utility.h"
#include <stdio.h>
#include <unistd.h>
#include "env/env.h"


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
int execute_command(const char *name, char **argl, char **envp, t_env *env)
{
	fprintf( tracciato, "execute_command(%s, char**, char**)\n", name );
	t_vec	path;
	int		i;
	char	*cmd;
	char	*tmp;

	(void)env;
	// print_env(env);
	fvec_init(&path, 0);
	expand_path(&path);
	i = 0;
	// printf("%s\n", name);
	if (check_builtins((char *)name) > 0)
	{
		printf("Inizio builtin: %s\n", name);
		if(exec_builtins((char *)name, argl, envp) == -1)
			{
				printf("oops\n");
				return(-1);
			}
		printf("Fine builtin: %s\n", name);
		return(1);  /// si eliminare questa riga e vedere l'output reale( con execve) e quello del nostro biultin!!!
	}
	while (path.size > i)
	{

		tmp = my_strjoin(path.tstr[i].s, "/");
		cmd = my_strjoin(tmp, name);
		free(tmp);
		// printf("%s\n", cmd);
		if (!access(cmd, X_OK))
		{
			if(-1 == execve(cmd, argl, envp))
				perror(cmd);
		}
		free(cmd);
		++i;
	}
	fvec_destroy(&path);
	return (1);
}

/*
Funzione take_commands: Questa funzione prepara un array di argomenti da passare a execute_command basandosi su un vettore di comandi (t_vec).
Filtra i comandi per redirezionamenti e parole, allocando dinamicamente spazio per gli argomenti e copiandoli. Alla fine, chiama execute_command
con il primo argomento come nome del comando.
*/
void take_commands(t_vec *cmd, char **envp, t_env *env)
{
	int i;
	int j;
	int len;
	char **args;

	i = 0;
	len = 0;
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
	execute_command(args[0], args, envp, env);
}

static int exec_echo(char *cmd, char **argl)
{
	int i = 1;
	(void)cmd;
	// printf("Inzio %s\n", cmd);
	while(argl[i] != 0)
		{
			printf("%s ", argl[i]);
			i++;
		}
	printf("\n");
	return(0);
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

int	check_builtins(char *cmd)
{
	fprintf( tracciato, "check_builtins(char *cmd)\n" );
	if (cmd && (my_strcmp(cmd, "export") == EQUAL))
		return (1);
	else if (cmd && (my_strcmp(cmd, "unset") == EQUAL))
		return (2);
	else if (cmd && (my_strcmp(cmd, "pwd") == EQUAL))
		return (3);
	else if (cmd && (my_strcmp(cmd, "exit") == EQUAL))
		return (4);
	else if (cmd && (my_strcmp(cmd, "cd") == EQUAL))
		return (5);
	else if (cmd && (my_strcmp(cmd, "env") == EQUAL))
		return (6);
	else if (cmd && (my_strcmp(cmd, "echo") == EQUAL))
		return (7);
	return (0);
}

int exec_builtins(char *cmd, char **argl,char **envp)
{
	fprintf( tracciato, "exec_builtins(char *cmd)\n" );
	
	int a;
	int b;
	(void )argl;
	(void )envp;
	a = check_builtins(cmd);
	b = -1;
	// if (a == 1)
	// 	b = exec_export();
	// else if (a == 2)
	// 	b = exec_unset();
	if (a == 3)
		b = exec_pwd(cmd);
	else if (a == 4)
		b = exec_exit(cmd);
	// else if (a == 5)
	// 	b = exec_cd();
	// else if (a == 6)
	// 	b = exec_env();
	else if (a == 7)
		b = exec_echo(cmd, argl);
	return(b);
}

int	exec_pwd(char *cmd)
{
	fprintf( tracciato, "exec_pwd(char *cmd)\n" );
	
	char	cwd[1024];
	char	*dir;

	(void)cmd;
	printf("I'm getting pwd...\n");
	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
	{
		perror("minishell: pwd: ");
		// g_data.exit_status = EXIT_FAILURE;
		return (-1);
	}
	printf("%s\n", dir);
	// g_data.exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

int	exec_exit(char *cmd)
{
	fprintf( tracciato, "exec_exit(char *cmd)\n" );

	printf("exit...3..2..1..\n");
	printf("fine builtin: %s\n", cmd);

	exit(223);
	return (0);
}

int exec_cd(char *cmd, char **ag, char **env)
{
	t_env	*ev;
	char	cwd[1024];
	char	owd[1024];

	env = start_env(env);
	if(arg[0])
	{
		if(chdir)
	}


}