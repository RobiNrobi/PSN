#ifndef MINISHELL_H
#define MINISHELL_H

#include "fvec2_man.h"
#include "env/env.h"


typedef struct s_global_info
{
	char	**env;
	t_vec2	*line;
}	t_gi;

int	minishell(char **envp);

#endif // MINISHELL_H
