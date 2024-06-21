#include "minishell.h"
#include "parser_man.h"
#include "command_v1.h"
#include <stdio.h>
#include <stdlib.h>

//TODO: remove the following
#include "../_extra.h"
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int main(int argc, char *argv[], char **envp)
{
	if (1 != argc)
	{
		(void)argv;
		//TODO: return an error here?
		return (13);
	}
	// TODO: remove the following
	if (!openf("tracciato.txt")) {
		printf( "Cannot open tracciato.txt.\n");
		return 0;
	}
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^
	if (minishell(envp))
	{
		// TODO: remove the following
		closef();
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^
		return (0);
	}
	// TODO: remove the following
	closef();
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^
	return (1);
}

int minishell(char **envp)
{
	fprintf( tracciato, "minishell()\n" );

	int		i;
	char	*line;
	t_vec2	vec2;

	line = NULL;
	i = 0;
	fvec2_init(&vec2, 0);
	if (!pars_parsline(line, &vec2))
		return (0);
	while (vec2.size > i)
	{
		take_commands(&vec2.tvec[i], envp);
		i++;
	}
	return (1);
}
