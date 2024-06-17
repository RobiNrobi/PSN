#include "parser_man.h"
// #include "utility.h"
#include "token_man.h"
#include "utility.h"
#include <stdlib.h>

//TODO: remove the following
#include "../_extra.h"
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int pars_expand_var(t_vec *vec, int ind, int ch)
{
	fprintf( tracciato, "pars_expand_var(t_vec*, %d, %d)\n", ind, ch );
	char	*new_s;

	new_s = getenv(&vec->tstr[ind].s[ch]);
	if (!new_s)
	{
		fprintf( tracciato, "...pars_expand_var()\tnew_s is NULL\n" );
		return (0);
	}
	fstr_replace_from_pos(&vec->tstr[ind], ch, new_s);
	return (1);
}

int pars_expand_vars(t_vec *vec)
{
	fprintf( tracciato, "pars_expand_vars(t_vec*)\n" );
	int	i;
	int	k;

	i = 0;
	while (vec->size > i)
	{
		k = 0;
		while (vec->tstr[i].size > k)
		{
			if ('$' == vec->tstr[i].s[k] &&
				(!k || my_isspace(vec->tstr[i].s[k - 1])))
				pars_expand_var(vec, i, k + 1);
			++k;
		}
		++i;
	}
	return (0);
}

int	pars_get_words_seq(t_vec *vec, char *line)
{
	fprintf( tracciato, "pars_get_words_seq(t_vec*, %s)\n", line );

	if (!fvec_init(vec, 0))
		return (0);
	token_pars_03(line, vec);
	return (1);
}

int pars_parsline(char *line)
{
	fprintf( tracciato, "parsline()\n" );
	t_vec	seq;

	//TODO: restore readline and delete the following lines:
	line = read_a_line("Viva Ansi!> ");
	// NOTE: the usage of readline() has been postponed because it causes memory
	//       leaks.
	// line = readline("Viva Ansi!> ");
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	//TODO: restore add_history:
	//	add_history(line);
	if (!line)
		return (0);
	if (token_error_quotes(line))
	{
		free(line);
		printf("Error: Unclosed quotes!\n");
		return (0);
	}
	pars_get_words_seq(&seq, line);
	fvec_print_vec(&seq);
	pars_expand_vars(&seq);
	fvec_print_vec(&seq);
	fvec_destroy(&seq);
	return (1);
}

void	close_laststr(t_str *str, t_vec *vec)
{
	fstr_add_char(str, '\0');
	fvec_add_str(vec, str);
	fstr_reset(str);
}
