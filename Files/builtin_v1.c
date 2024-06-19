#include "builtin_v1.h"
#include "utility.h"

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/*
** From the assignment:
** Your shell must implement the following builtins:
**     echo
**     cd
**     pwd
**     export
**     unset
**     env
**     exit
*/
int is_builtin_cmd(char const *const s)
{
	fprintf( tracciato, "is_builtin_cmd(%s)\n", s );
	if (!my_strcmp(s, "echo")      || !my_strcmp(s, "cd")
		|| !my_strcmp(s, "pwd")    || !my_strcmp(s, "export")
		|| !my_strcmp(s, "unset")  || !my_strcmp(s, "env")
		|| !my_strcmp(s, "exit"))
		return (1);
	return (0);
}
