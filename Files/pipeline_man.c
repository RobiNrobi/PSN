#include "pipeline_man.h"
#include "command_v1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void pipe_break_pipe(t_vec2 *v2, t_fd *fcs)
{
	(void)fcs;
	t_pi	pi;
	int		i;

	pipe_init_pipe(&pi);
	i = 0;
	while (v2->size > i)
	{
		pi.cmds = &v2->tvec[i];
		comm_parse_cmd(&pi);
		++i;
	}
}

void pipe_create_pipes(t_vec2 *v2, t_fd *fcs)
{
	int		i;

	i = 0;
	while (v2->size > i)
	{
		if (0 > pipe(&fcs[i * 2].child))
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		++i;
	}
}

void pipe_execute_pipe(t_vec2 *v2)
{
	t_fd	*fc;
	pid_t	*pids;
	int		i;

	fc = malloc(sizeof(t_fd) * (size_t)(2 * (v2->size - 1)));
	pids = malloc(sizeof(pid_t) * (size_t)v2->size);
	pipe_create_pipes(v2, fc);
	i = 0;
	while (v2->size > i)
	{
		pipe_break_pipe(v2, fc);
		++i;
	}
	free(fc);
	free(pids);
}

void pipe_init_pipe(t_pi *pi)
{
	pi->pipe_fds = NULL;
	pi->cmds = NULL;
	pi->infile = NULL;
	pi->outfile = NULL;
	pi->here_doc = NULL;
	pi->append = 0;;

}
