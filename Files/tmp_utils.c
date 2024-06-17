#include "tmp_utils.h"
#include <stdlib.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

t_vec *expand_path(t_vec *v)
{
	fprintf( tracciato, "expand_path(t_vec*)\n" );
	char	*path;
	t_str	ts;

	path = getenv("PATH");
	fstr_init(&ts, 100);
	while (*path)
	{
		if (':' != *path)
			fstr_add_char(&ts, *path);
		else
		{
			fstr_add_char(&ts, '\0');
			fvec_add_str(v, &ts);
			fstr_reset(&ts);
		}
		++path;
	}
	fstr_destroy(&ts);
	fvec_print_vec(v);
	return (v);
}

// Funzione per convertire l'enumerazione in una stringa
// Da cancellare
// const char* state_to_string(t_state state)
// {
// 	switch (state) {
// 	case dq: return "dq"; break;
// 	case sq: return "sq"; break;
// 	case less: return "less"; break;
// 	case lessless: return "lessless"; break;
// 	case great: return "great"; break;
// 	case greatgreat: return "greatgreat"; break;
// 	case pipes: return "pipe"; break;
// 	case word: return "word"; break;
// 	default: return "unknown"; break;
// 	}
// }
