#include "minishell.h"
#include "parser_man.h"
#include <stdio.h>
#include <stdlib.h>

//TODO: remove the following
#include "../_extra.h"
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int main(int argc, char *argv[])
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
	if (minishell())
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

int minishell(void)
{
	fprintf( tracciato, "minishell()\n" );
	char	*line;

	line = NULL;
	if (!pars_parsline(line))
		return (0);
	return (1);
}
