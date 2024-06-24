#include <ctype.h>
// #include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 10
#define BUFFER_SIZE 1024
#define HISTORY_SIZE 100


volatile sig_atomic_t	keep_running = 1;

char	*history[HISTORY_SIZE];
int		history_count = 0;
int		last_exit_status = 0;

void	add_to_history(const char *command);
int		execute_builtin_command(char **args);
int		execute_bunch(void);
void	execute_pipeline(char *commands[], int n);
char	*expand_variables(const char *input);
void	handle_signal(int signal);
int		is_builtin_command(char **args);
void	parse_command(char *command, char **args, char **input_file,
				   char **output_file, char **here_document, int *append);
void	print_history(void);
void	setup_signal_handlers(void);
void	handle_here_document(char *delimiter, int pipefd[2]);

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\nmysh> ");
		fflush(stdout);
	}
	else if (signal == SIGQUIT)
	{
		printf("\nQuit (core dumped)\n");
		exit(EXIT_SUCCESS);
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction sa;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	add_to_history(const char *command)
{
	if (history_count < HISTORY_SIZE)
	{
		history[history_count++] = strdup(command);
	}
	else
	{
		free(history[0]);
		memmove(history, history + 1, (HISTORY_SIZE - 1) * sizeof(char *));
		history[HISTORY_SIZE - 1] = strdup(command);
	}
}

void	print_history(void)
{
	for (int i = 0; i < history_count; i++)
	{
		printf("%d %s\n", i + 1, history[i]);
	}
}

char	*expand_variables(const char *input)
{
	static char buffer[BUFFER_SIZE];
	char *out = buffer;
	const char *in = input;

	while (*in)
	{
		if (*in == '$')
		{
			if (*(in + 1) == '?')
			{
				in += 2;
				out += sprintf(out, "%d", last_exit_status);
			}
			else
			{
				const char *start = ++in;
				while (*in && (isalnum(*in) || *in == '_'))
				{
					in++;
				}
				int len = (int)(in - start);
				char var[len + 1];
				strncpy(var, start, (size_t)len);
				var[len] = '\0';
				char *value = getenv(var);
				if (value)
				{
					out += sprintf(out, "%s", value);
				}
			}
		}
		else
		{
			*out++ = *in++;
		}
	}
	*out = '\0';
	return (buffer);
}

void	parse_command(char *command, char **args, char **input_file,
		char **output_file, char **here_document, int *append)
{
	int i = 0;
	char *token;
	*input_file = NULL;
	*output_file = NULL;
	*here_document = NULL;
	*append = 0;

	char *temp = strtok(command, " ");
	while (temp != NULL && i < MAX_ARGS - 1)
	{
		token = temp;
		if (token[0] == '\'')
		{
			token++;
			while (temp[strlen(temp) - 1] != '\'')
			{
				temp = strtok(NULL, " ");
				if (temp == NULL)
				{
					fprintf(stderr, "Error: unmatched single quote\n");
					exit(EXIT_FAILURE);
				}
				strcat(token, " ");
				strcat(token, temp);
			}
			token[strlen(token) - 1] = '\0';
		}
		else if (token[0] == '"')
		{
			token++;
			while (temp[strlen(temp) - 1] != '"')
			{
				temp = strtok(NULL, " ");
				if (temp == NULL)
				{
					fprintf(stderr, "Error: unmatched double quote\n");
					exit(EXIT_FAILURE);
				}
				strcat(token, " ");
				strcat(token, temp);
			}
			token[strlen(token) - 1] = '\0';
		}
		if (strcmp(token, "<") == 0)
		{
			temp = strtok(NULL, " ");
			if (temp == NULL)
			{
				fprintf(stderr, "Error: expected filename after '<'\n");
				exit(EXIT_FAILURE);
			}
			*input_file = temp;
		}
		else if (strcmp(token, ">") == 0)
		{
			temp = strtok(NULL, " ");
			if (temp == NULL)
			{
				fprintf(stderr, "Error: expected filename after '>'\n");
				exit(EXIT_FAILURE);
			}
			*output_file = temp;
			*append = 0;
		}
		else if (strcmp(token, ">>") == 0)
		{
			temp = strtok(NULL, " ");
			if (temp == NULL)
			{
				fprintf(stderr, "Error: expected filename after '>>'\n");
				exit(EXIT_FAILURE);
			}
			*output_file = temp;
			*append = 1;
		}
		else if (strcmp(token, "<<") == 0)
		{
			temp = strtok(NULL, " ");
			if (temp == NULL)
			{
				fprintf(stderr, "Error: expected delimiter after '<<'\n");
				exit(EXIT_FAILURE);
			}
			*here_document = temp;
		}
		else
		{
			args[i++] = token;
		}
		temp = strtok(NULL, " ");
	}
	args[i] = NULL;
}

void	handle_here_document(char *delimiter, int pipefd[2])
{
	close(pipefd[0]); // Close read end of the pipe
	FILE *pipe_write = fdopen(pipefd[1], "w");
	if (!pipe_write)
	{
		perror("fdopen");
		exit(EXIT_FAILURE);
	}

	char buffer[BUFFER_SIZE];
	printf("heredoc> ");
	while (fgets(buffer, BUFFER_SIZE, stdin))
	{
		if (strncmp(buffer, delimiter, strlen(delimiter)) == 0
			&& buffer[strlen(delimiter)] == '\n')
		{
			break ;
		}
		fprintf(pipe_write, "%s", buffer);
		printf("heredoc> ");
	}
	fclose(pipe_write);
	exit(EXIT_SUCCESS);
}

int	is_builtin_command(char **args)
{
	return (strcmp(args[0], "echo") == 0 || strcmp(args[0], "cd") == 0
		|| strcmp(args[0], "pwd") == 0 || strcmp(args[0], "export") == 0
		|| strcmp(args[0], "unset") == 0 || strcmp(args[0], "env") == 0
		|| strcmp(args[0], "exit") == 0 || strcmp(args[0], "history") == 0);
}

int	execute_builtin_command(char **args)
{
	if (strcmp(args[0], "echo") == 0)
	{
		int newline = 1;
		int start = 1;
		if (args[1] && strcmp(args[1], "-n") == 0)
		{
			newline = 0;
			start = 2;
		}
		for (int i = start; args[i]; i++)
		{
			printf("%s", args[i]);
			if (args[i + 1])
			{
				printf(" ");
			}
		}
		if (newline)
		{
			printf("\n");
		}
		return (0);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			args[1] = getenv("HOME");
		}
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	else if (strcmp(args[0], "pwd") == 0)
	{
		char cwd[BUFFER_SIZE];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
		}
		else
		{
			perror("pwd");
			return (1);
		}
		return (0);
	}
	else if (strcmp(args[0], "export") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "export: usage: export NAME=VALUE\n");
			return (1);
		}
		char *name = strtok(args[1], "=");
		char *value = strtok(NULL, "=");
		if (name && value)
		{
			setenv(name, value, 1);
		}
		else
		{
			fprintf(stderr, "export: invalid argument\n");
			return (1);
		}
		return (0);
	}
	else if (strcmp(args[0], "unset") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "unset: usage: unset NAME\n");
			return (1);
		}
		unsetenv(args[1]);
		return (0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		extern char **environ;
		for (char **env = environ; *env; env++)
		{
			printf("%s\n", *env);
		}
		return (0);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(args[0], "history") == 0)
	{
		print_history();
		return (0);
	}
	return (1);
}

void	execute_pipeline(char *commands[], int n)
{
	int pipefds[2 * (n - 1)];
	pid_t pids[MAX_COMMANDS];

	// Create pipes
	for (int i = 0; i < n - 1; i++)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}

	int j = 0;
	for (int i = 0; i < n; i++)
	{
		int here_pipe[2];
		char *args[MAX_ARGS];
		char *input_file = NULL;
		char *output_file = NULL;
		char *here_document = NULL;
		int append = 0;

		parse_command(commands[i], args, &input_file, &output_file,
			&here_document, &append);

		if (is_builtin_command(args))
		{
			last_exit_status = execute_builtin_command(args);
			continue ;
		}

		if (here_document)
		{
			if (pipe(here_pipe) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			if (fork() == 0)
			{
				handle_here_document(here_document, here_pipe);
			}
		}

		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pids[i] == 0)
		{
			// Redirect input from previous pipe
			if (i > 0)
			{
				if (dup2(pipefds[j - 2], 0) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}

			// Redirect output to next pipe
			if (i < n - 1)
			{
				if (dup2(pipefds[j + 1], 1) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}

			// Handle input redirection
			if (input_file != NULL)
			{
				int fd_in = open(input_file, O_RDONLY);
				if (fd_in < 0)
				{
					perror("open input file");
					exit(EXIT_FAILURE);
				}
				if (dup2(fd_in, 0) < 0)
				{
					perror("dup2 input file");
					close(fd_in);
					exit(EXIT_FAILURE);
				}
				close(fd_in);
			}

			// Handle output redirection
			if (output_file != NULL)
			{
				int fd_out;
				if (append)
				{
					fd_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND,
							0644);
				}
				else
				{
					fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC,
							0644);
				}
				if (fd_out < 0)
				{
					perror("open output file");
					exit(EXIT_FAILURE);
				}
				if (dup2(fd_out, 1) < 0)
				{
					perror("dup2 output file");
					close(fd_out);
					exit(EXIT_FAILURE);
				}
				close(fd_out);
			}

			// Handle here document
			if (here_document)
			{
				close(here_pipe[1]);
				if (dup2(here_pipe[0], 0) < 0)
				{
					perror("dup2 here document");
					close(here_pipe[0]);
					exit(EXIT_FAILURE);
				}
				close(here_pipe[0]);
			}

			// Close all pipe file descriptors
			for (int k = 0; k < 2 * (n - 1); k++)
			{
				close(pipefds[k]);
			}

			if (execvp(args[0], args) < 0)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}

		if (here_document)
		{
			close(here_pipe[0]);
			close(here_pipe[1]);
		}
		j += 2;
	}

	// Close all pipe file descriptors in the parent
	for (int i = 0; i < 2 * (n - 1); i++)
	{
		close(pipefds[i]);
	}

	// Wait for all child processes
	for (int i = 0; i < n; i++)
	{
		int status;
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			last_exit_status = WEXITSTATUS(status);
		}
		else
		{
			last_exit_status = 1;
		}
	}
}

int	execute_bunch(void)
{
	setup_signal_handlers();

	while (keep_running)
	{
		printf("mysh> ");
		fflush(stdout);

		char input[BUFFER_SIZE];
		if (fgets(input, BUFFER_SIZE, stdin) == NULL)
			break ;
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';
		if (!strlen(input))
			continue ;
		add_to_history(input);
		char expanded_input[BUFFER_SIZE];
		strcpy(expanded_input, expand_variables(input));

		char *commands[MAX_COMMANDS];
		int num_commands = 0;
		char *command = strtok(expanded_input, "|");
		while (command != NULL && num_commands < MAX_COMMANDS)
		{
			commands[num_commands++] = command;
			command = strtok(NULL, "|");
		}

		execute_pipeline(commands, num_commands);
	}

	return (0);
}
