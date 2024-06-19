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

	fvec_init(&path, 0);
	expand_path(&path);
	i = 0;
	while (path.size > i)
	{
		cmd = my_strjoin(path.tstr[i].s, name);
		if (!access(cmd, X_OK))
			if (-1 == execve(cmd, argl, envp))
				perror(cmd);
		free(cmd);
		++i;
	}
	fvec_destroy(&path);
	return (1);
}
