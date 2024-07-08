#include "command_v1.h"
#include "builtin_v1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int exec_cd(char *cmd, char **ag, char **env)
{
	(void)cmd;
	(void)ag;
	(void)env;
	//	t_env	*ev;
	//	char	cwd[1024];
	//	char	owd[1024];

	//	env = start_env(env);
	//	if(arg[0])
	//	{
	//		if(chdir)
	//	}
	return (0);
}

int exec_echo(char *cmd, char **argl)
{
	int i = 1;
	(void)cmd;
	while(argl[i] != 0)
	{
		printf("%s ", argl[i]);
		i++;
	}
	printf("\n");
	return(0);
}

int exec_builtins(char *cmd, char **argl,char **envp)
{
	fprintf( tracciato, "exec_builtins(char *cmd)\n" );

	int a;
	int b;
	(void )argl;
	(void )envp;
	a = built_is_builtin_cmd(cmd);
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

int	exec_exit(char *cmd)
{
	fprintf( tracciato, "exec_exit(char *cmd)\n" );
	printf("exit...3..2..1..\n");
	printf("fine builtin: %s\n", cmd);

	exit(223);
	return (0);
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

/*
** From man pipe
** -------------
** #include <fcntl.h>              // Definition of O_* constants
** #include <unistd.h>
** int pipe2(int pipefd[2], int flags);
**
** DESCRIPTION
** pipe() creates a pipe, a unidirectional data channel that can be used for
** interprocess communication.
** The array pipefd is used to return two file descriptors referring to the
** ends of the pipe.
** pipefd[0] refers to the read end of the pipe.
** pipefd[1] refers to the write end of the pipe.
** Data written to the write end of the pipe is buffered by the kernel until it
** is read from the read end of the pipe.
**
** RETURN VALUE
** On success, zero is returned. On error, -1 is returned, errno is set to
** indicate the error, and pipefd is left unchanged.
**
** EXAMPLES
** The following program creates a pipe, and then fork(2)s to create a child
** process; the child inherits a duplicate set of file descriptors that refer
** to the same pipe.
** After the fork(2), each process closes the file descriptors that it doesn't
** need for the pipe [...].
** The parent then writes the string contained in the program's command-line
** argument to the pipe, and the child reads this string a byte at a time from
** the pipe and echoes it on standard output.
** #include <stdio.h>
** #include <stdlib.h>
** #include <string.h>
** #include <sys/types.h>
** #include <sys/wait.h>
** #include <unistd.h>
**
** int main(int argc, char *argv[])
** {
**     int    pipefd[2];
**     char   buf;
**     pid_t  cpid;
**
**     if (pipe(pipefd) == -1) {
**         perror("pipe");
**         exit(EXIT_FAILURE);
**     }
**
**     cpid = fork();
**     if (cpid == -1) {
**         perror("fork");
**         exit(EXIT_FAILURE);
**     }
**
**     if (cpid == 0) {               // Child reads from pipe
**         close(pipefd[1]);          // Close unused write end
**
**         while (read(pipefd[0], &buf, 1) > 0)
**             write(STDOUT_FILENO, &buf, 1);
**
**         write(STDOUT_FILENO, "\n", 1);
**         close(pipefd[0]);
**         _exit(EXIT_SUCCESS);
**
**     } else {                       // Parent writes argv[1] to pipe
**         close(pipefd[0]);          // Close unused read end
** 	       write(pipefd[1], argv[1], strlen(argv[1]));
** 	       close(pipefd[1]);          // Reader will see EOF
** 	       wait(NULL);                // Wait for child
** 	       exit(EXIT_SUCCESS);
**    }
** }
*/

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
