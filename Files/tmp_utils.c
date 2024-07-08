#include "tmp_utils.h"
#include "utility.h"
#include <stdlib.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int count_elem_in_charpp(char **s)
{
	fprintf( tracciato, "count_elem_in_charpp(char**)\n" );
	int howmany;

	if (!s || !*s)
		return (0);
	howmany = 0;
	while (s[howmany])
		++howmany;
	return (howmany);
}

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
	return (v);
}

void free_charpp(char **ss)
{
	fprintf( tracciato, "free_charpp(char**)\n" );
	char	**p;

	if (!ss)
		return ;
	p = ss;
	while (*ss) {
		free(*ss++);
	}
	free(p);
}

int is_quote_or_pipe(int ch)
{
	fprintf( tracciato, "is_quote_or_pipe(%c)\n", ch );
	return (is_any_of(ch, "|\"'"));
}

int is_redirect(t_str *tstr)
{
	fprintf( tracciato, "is_redirect(t_str)\n" );
	if (tstr->state == less || tstr->state == less
		|| tstr->state == great || tstr->state == greatgreat)
		return (1);
	else
		return (0);
}

void print_charpp(char **s)
{
	fprintf( tracciato, "fvec2_print_charpp(char**)\n" );
	int i;

	if (!s || !*s)
		return ;
	i = 0;
	while (s && s[i])
	{
		printf( "%s\n", s[i] );
		++i;
	}
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


/*
** cfr. fvec2_deep_copy()
*/
// int expand_env(t_vec2 *v2, char **s)
// {
// 	fprintf( tracciato, "expand_env(t_vec2*, char**)\n" );
// 	int		i;
// 	int		k;
// 	t_vec	v;
// 	t_str	ts;

// 	if (!s || !*s)
// 		return (0);
// 	fvec_init(&v, 0);
// 	fstr_init(&ts, 0);
// 	i = 0;
// 	while (s[i])
// 	{
// 		k = 0;
// 		while ('=' != s[i][k])
// 		{
// 			fstr_add_char(&ts, s[i][k]);
// 			++k;
// 		}
// 		fvec_close_add_str(&v, &ts);
// 		fstr_reset(&ts);
// 		++k;
// 		while (s[i][k] && '\n' != s[i][k])
// 		{
// 			fstr_add_char(&ts, s[i][k]);
// 			++k;
// 		}
// 		fvec_close_add_str(&v, &ts);
// 		fvec2_add_vec(v2, &v);
// 		fstr_reset(&ts);
// 		fvec_reset(&v);
// 		++i;
// 	}
// 	fstr_destroy(&ts);
// 	fvec_destroy(&v);
// 	return (1);
// }
