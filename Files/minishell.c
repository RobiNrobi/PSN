#include "minishell.h"
#include "parser_man.h"
#include "command_v1.h"
#include "env/env.h"
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
	t_env	*env; // eliminare

	env = start_env(envp); // eliminare
	line = NULL;
	fvec2_init(&vec2, 0);
	if (!pars_parsline(line, &vec2))
		return (0);
	i = 0;
	// SPOSTARE IN UNA FUNZIONE CHE SEGUE LO SCHEMA "execute pipeline()"
	while (vec2.size > i)
	{
		comm_take_cmds(&vec2.tvec[i], envp, env);
		i++;
//		take_commands(&vec2.tvec[i], envp, env);
//		break;
	}
	return (1);
}
