#include "tmp_utils.h"
#include "utility.h"
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
			fvec_close_add_str(v, &ts);
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

int is_quote_or_pipe(int ch)
{
	fprintf( tracciato, "is_quote_or_pipe(%c)\n", ch );
	return (is_any_of(ch, "|\"'"));
}

/*
	se virgolette doppie
		se virgolette doppie aperte
			chiudi virgolette doppie
		altrimenti
			se virgolette singole chiuse
				apri virgolette doppie
	altrimenti
		se virgolette singole
			se virgolette singole aperte
				chiudi virgolette singole
			altrimenti
				se virgolette doppie chiuse
					apri virgolette singole
*/
int switch_quo(int ch, int *dquo, int *squo)
{
	fprintf( tracciato, "switch_quo(%c, %d, %d)\n", ch, *dquo, *squo );
	if ('"' == ch)
	{
		if (*dquo)
			*dquo = 0;
		else if (!*squo)
			*dquo = 1;
	}
	else if ('\'' == ch)
	{
		if (*squo)
			*squo = 0;
		else if (!*dquo)
			*squo = 1;
	}
	return (*squo | *dquo);
}
