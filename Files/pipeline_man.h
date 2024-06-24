#ifndef PIPELINE_MAN_H
#define PIPELINE_MAN_H

#include "fvec2_man.h"
#include <fcntl.h>

typedef struct s_pipe_info
{
	int		fd[2];
	pid_t	pid;
	t_vec	*cmds;
	char	*infile;
	char	*outfile;
	char	*here_doc;
	int		append;
}	t_pi;

void	pipe_break_pipe(t_vec2 *v2, t_fd *fcs);
void	pipe_create_pipes(t_vec2 *v2, t_fd *fcs);
void	pipe_execute_pipe(t_vec2 *v2);
void	pipe_init_pipe(t_pi *pi);

#endif // PIPELINE_MAN_H
