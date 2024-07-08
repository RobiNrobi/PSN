#include "fvec2_man.h"
#include "parser_man.h"
#include "tmp_utils.h"
#include "token_man.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: remove the following
#include "../_extra.h"
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/*
** pars_check_syntax() gets through each t_str inside the t_vec inside the
** passed t_vec2 and checks whether every redirection symbol is followed by
** a string (that could be a file name) or not.
** If a redirection symbol is not followed by a string it forces exit.
*/
void pars_check_syntax(t_vec2 *cmds)
{
	fprintf( tracciato, "pars_check_syntax(t_vec2*)\n" );
	t_vec seq;
	int i;
	int j;

	j = 0;
	i = 0;
	while (cmds->size > i)
	{	seq = cmds->tvec[i];
		while (seq.size > j)
		{
			if (is_redirect(&seq.tstr[j]) && seq.tstr[j + 1].state != word)
			{
				display_error_syntax(seq.tstr[j + 1].s);
				fvec2_destroy(cmds);
				closef();
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
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
				tvec_update_env_value(vec, i, k + 1);
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

void pars_pars_on_pipes(t_vec *tv, char *line)
{
	fprintf( tracciato, "pars_pars_on_pipes(t_vec*, %s)\n", line );
	int		in_dquotes;
	int		in_squotes;
	int		pipe;
	t_str	tstr;

	in_dquotes = 0;
	in_squotes = 0;
	pipe = 0;
	fstr_init(&tstr, 0);
	while (*line)
	{
		if (*line == '\"' || *line == '\'')
			switch_quo(*line, &in_squotes, &in_dquotes);
		if (*line == '|')
		{
			if (in_dquotes || in_squotes)
			{
				pipe = 0;
				fstr_add_char(&tstr, *line);
			}
			else
			{
				pipe = 1;
				fstr_add_char(&tstr, *line);
				fvec_close_add_str(tv, &tstr);
				fstr_reset(&tstr);
			}
		}
		else
		{
			fstr_add_char(&tstr, *line);
			if (!my_isspace(*line))
				pipe = 0;
		}
		++line;
	}
	if (pipe)
	{
		line = read_a_line("> ");
		if (token_error_quotes(line))
			exit(EXIT_FAILURE);
		pars_pars_on_pipes(tv, line);
		free(line);
	}
	if (tstr.s[0])
		fvec_close_add_str(tv, &tstr);
	fstr_destroy(&tstr);
}

int pars_parsline(char *line, t_vec2 *cmds)
{
	fprintf( tracciato, "pars_parsline()\n" );
	t_vec	seq;
	t_vec	seq2;

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
	if (*line == '|' || token_error_quotes(line))
	{
		if (*line == '|')
			display_error_syntax(" `|'");
		else
			display_error("Error: Unclosed quotes!\n");
		free(line);
		return (0);
	}
	fvec_init(&seq, 0);
	pars_pars_on_pipes(&seq, line);

	int	i;
	i = 0;
	fvec_init(&seq2, 0);
	while (seq.size > i)
	{
		token_pars_03(seq.tstr[i].s, &seq2);
		fvec2_add_vec(cmds, &seq2);
		fvec_reset(&seq2);
		++i;
	}
	free(line);
	fvec_destroy(&seq2);
	fvec_destroy(&seq);
	pars_check_syntax(cmds);
	return (1);
}
