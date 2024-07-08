#ifndef PIPELINE_MAN_H
#define PIPELINE_MAN_H

#include "fvec2_man.h"
#include <fcntl.h>

/*
** s_pipe_info is supposed to be instanced once per each command, but it has
** been created only to overcome the 4 paramethers limit of the 42 Norm.
** fd_pipes --> files descriptor of each command (at least STDIN_FILENO and
**             STDOUT_FILENO) for communication
** pid --> process identifier; it is usually needed to find the 'child'
**        (0 == pd) process.
** args --> the command to be executed toghether with its arguments the command 
** is supposed to be the first char*
** infile --> the name of the file from which redirect.
** outfile --> the name of the file to redirect to.
** here_doc --> ???
** append --> in case we need to manage a redirection, it speciies we need to
**            append to the file (">>") rather then overwrite ('>') it.
** env --> stores a bunch of information about the current Linux environment;
**         in short, it comes from the Linux "env" command, which deliveries
**         such information in the form of a list of KEY=TEXT WITH SPACES lines;
**         in the t_vec, they are brocken into a t_str[0] --> KEY and a
**         t_str[1] --> TEXT WITH SPACES couple.
** cmd --> cmd to execute together with its path
** As each struct, it is strongly suggested to set all properties to 0/NULL;
** to that purpos, the comm_pipe_init() function has been provided, but please
** keep in mind that function does not reserve any memory.
*/

typedef struct s_pipe_info
{
	int		fd_pipes[2];
	pid_t	pid;
	char	**args; // args[0] e' cmd senza la path
	char	*infile;
	char	*outfile;
	char	*here_doc;
	int		append;
	char	*cmd; // PATH included
	char	**env;
}	t_pi;

// void	pipe_break_pipe(t_vec2 *v2, t_pi pipe);
// void	pipe_create_pipes(t_vec2 *v2, t_pi pipe_info);
// void	pipe_execute_pipe(t_vec2 *v2);

void	pipe_init_pipe(t_pi *pi);
void 	pipe_open_pipes(t_vec2 *vec2, char **envp);
void	pipe_tell_cmds_apart(t_vec *cmd, char **envp, t_pi *pi);
void 	pipe_parse_redirect(t_pi *pi, t_vec *vec, int *i);
int		pipe_add_path_to_cmd(t_pi *pi);

int		pipe_execute_cmd(t_pi *pi, char **envp);

int		pipe_count_words_in_tvec(t_vec *v);

#endif // PIPELINE_MAN_H
