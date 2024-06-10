#include "parser_man.h"
#include "fvec_man.h"
#include "utility.h"
#include "../_extra.h"
// #include <readline/readline.h>
// #include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

//TODO: remove the following
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

t_vec *pars_char_by_char(t_vec *vec, char *str)
{
	fprintf( tracciato, "pars_char_by_char(t_vec*, %s)\n", str );
	int	wopen;
	t_str	ts;

	wopen = 0;
	fstr_init(&ts, 0);
	while (*str)
	{
		if (my_isspace(*str))
		{
			if (wopen)
			{
				wopen = 0;
				fvec_add_str(vec, &ts);
				fstr_reset(&ts);
			}
		}
		else
		{
			wopen = 1;
			fstr_add_char(&ts, *str);
		}
		++str;
	}
	fvec_add_str(vec, &ts);
	free(ts.s);
	return (vec);
}

t_vec	*pars_get_words_seq(t_vec *vec, char *str)
{
	fprintf( tracciato, "pars_get_words_seq(t_vec*, %s)\n", str );
	// fvec_init(vec, 0);
	// str = pars_skip_spaces(str);
	// pars_char_by_char(vec, str);
	t_vec2 vec2;
	fvec2_init(&vec2, 0);
	pars_03(str, &vec2);
	fvec2_destroy(&vec2);
	exit(EXIT_FAILURE);
	// fvec_print_vec(vec);
	return vec;
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
	pars_get_words_seq(&seq, line);
	fvec_destroy(&seq);
	free(line);
	return (1);
}

char *pars_skip_spaces(char *str)
{
	fprintf( tracciato, "pars_skip_spaces(%s)\n", str );
	if (!str)
		return (NULL);
	while (!(my_isspace(*str)))
		++str;
	return (str);
}

/*
** pars_getword(): the t_str* must has already been initialized
*/
int pars_getword(char *line, t_str *str)
{
	int i;
	int parens;
	int	ret;

	i = 0;
	while (line[i] && my_isspace(line[i]))
		++i;
	parens = 0;
	ret = 0;
	if ('"' == line[i])
		parens = 1;
	while (line[i] && !ret)
	{
		if (parens)
		{
			if ('"' == line[i])
				ret = 1;
			if (my_isprint(line[i]) && !ret)
				fstr_add_char(str, line[i]);
		}
		else
		{
			if ('"' == line[i])
				ret = 2;
			if (my_isalnum(line[i]) && !ret)
				fstr_add_char(str, line[i]);
		}
		++i;
	}
	fstr_add_char(str, '\0');
	return (ret);
}


/*
** dq: double quote (') opened?
** sq: sinqle quote (') opened?
** word: a character which is neither a 'space' or a 'metachar' have been met
*/

/*
** vec2 must has already been initialized
*/

int pars_03(char *line, t_vec2 *vec2)
{
	fprintf( tracciato, "pars_03(%s, t_vec2*)\n", line );
	int		i;
	t_vec	vec;
	t_str	str;

	i = 0;
	// fvec2_init(vec2, 0);
	if (!fvec_init(&vec, 0))
		return (0);
	if (!fstr_init(&str, 0))
	{
		fvec_destroy(&vec);
		return (0);
	}
	while (line[i] && my_isspace(line[i]))
		++i;
	while (line[i])
	{
		if ('"' == line[i] || '\'' == line[i])
		{
			if ((str.s[0]) && !str.pd.less && !str.pd.lessless)
			{
				fstr_add_char(&str, '\0');
				fvec_add_str(&vec, &str);
				fstr_reset(&str);
				fstr_add_char(&str, line[i]);
				if (line[i] == '"')
					str.pd.dq = 1;
				else 
					str.pd.sq = 1;
				i++;
			}
			else if (!str.s[0] || str.pd.less || str.pd.lessless)
			{
				fstr_add_char(&str, line[i]);
				if (line[i] == '"')
					str.pd.dq = 1;
				else
					str.pd.sq = 1;
				i++;
			}
			while ((str.pd.dq == 1 || str.pd.sq == 1) && line[i])
			{
				if (line[i] == '"' || line[i] == '\'')
				{
					fstr_add_char(&str, line[i]);
					fstr_add_char(&str, '\0');
					fvec_add_str(&vec, &str);
					fstr_reset(&str);
					i--;
				}
				else
					fstr_add_char(&str, line[i]);
				i++;
				if (!line[i] && (str.pd.dq == 1 || str.pd.sq == 1))
				{
					printf("fanculo!\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		else if (my_isalnum(line[i]))
		{
			str.pd.less = 0;
			if (!str.pd.word && str.s[0])
			{
				str.pd.word = 1;
				fstr_add_char(&str, '\0');
				fvec_add_str(&vec, &str);
				fstr_reset(&str);
			}
			fstr_add_char(&str, line[i]);
			str.pd.word = 1;
		}
		else if (my_isspace(line[i]))
		{
			if (str.pd.word)
			{
				str.pd.word = 0;
				fstr_add_char(&str, '\0');
				fvec_add_str(&vec, &str);
				fstr_reset(&str);
			}
		}
		else if ('<' == line[i])
		{
			if ('<' != line[i + 1])
				str.pd.less = 1;
			else
				str.pd.lessless = 1;
			if (str.s[0])
			{
				fstr_add_char(&str, '\0');
				fvec_add_str(&vec, &str);
				fstr_reset(&str);
				fstr_add_char(&str, line[i]);
				if (line[i + 1] == '<')
					fstr_add_char(&str, line[++i]);
				fstr_add_char(&str, '\0');
				fvec_add_str(&vec, &str);
				fstr_reset(&str);
			}
			else
			{
				fstr_add_char(&str, line[i]);
				if (line[i + 1] == '<')
					fstr_add_char(&str, line[++i]);
				fstr_add_char(&str, '\0');
				fvec_add_str(&vec, &str);
				fstr_reset(&str);
			}
		}
	++i;
	}
	if (str.pd.word)
	{
		fprintf(tracciato, "last Word\n");
		fstr_add_char(&str, '\0');
		fvec_add_str(&vec, &str);
		fstr_reset(&str);
		fvec2_add_vec(vec2, &vec);
	}
	fvec_print_vec(&vec);
	// fvec2_print_vec2(vec2);
	// fstr_destroy(&str);
	// fvec_destroy(&vec);
	// free(vec.tstr);
	// free(str.s);
	exit(EXIT_FAILURE);
	return (1);
}
