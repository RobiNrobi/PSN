#include "fvec2_man.h"
#include "parser_man.h"
#include "tmp_utils.h"
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
	t_vec	seq2;
	t_vec2	cmds;

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

	// NOTE: VARIATION FROM 2024-06-18
	// t_vec2 instead of t_vec
	// 'line' is split into chunks on pipes ('|') and only later, t_vec by
	//  t_vec, on spaces and metacharacters
	fvec_init(&seq, 0);
	pars_pars_on_pipes(&seq, line);
	fvec_print_vec(&seq);

	int	i;
	i = 0;
	fvec2_init(&cmds, 0);
	fvec_init(&seq2, 0);
	while (seq.size > i)
	{
		token_pars_03(seq.tstr[i].s, &seq2);
		fvec2_add_vec(&cmds, &seq2);
		fvec_reset(&seq2);
		++i;
	}
	fvec2_print_vec2(&cmds);
	// pars_get_words_seq(&seq, line);
	// fvec_print_vec(&seq);
	fvec_destroy(&seq2);
	fvec_destroy(&seq);
	fvec2_destroy(&cmds);
	free(line);
	return (1);
}

void pars_pars_on_pipes(t_vec *tv, char *line)
{
	int		in_dquotes;
	int		in_squotes;
	t_str	tstr;

	in_dquotes = 0;
	in_squotes = 0;
	fstr_init(&tstr, 0);
	while (*line)
	{
		if (is_quote_or_pipe(*line))
		{
			if ('|' == *line)
			{
				if (in_dquotes || in_squotes)
					fstr_add_char(&tstr, *line);
				else
				{
					fvec_close_add_str(tv, &tstr);
					fstr_reset(&tstr);
				}
			}
			else
				switch_quo(*line, &in_squotes, &in_dquotes);
		}
		else
			fstr_add_char(&tstr, *line);
		++line;
	}
	fvec_close_add_str(tv, &tstr);
	fstr_destroy(&tstr);
}
