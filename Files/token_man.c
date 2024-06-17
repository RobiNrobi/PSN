#include "token_man.h"
#include "utility.h"

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void token_dollar(t_pi *pi, t_str *str)
{
	fprintf( tracciato, "token_dollar(t_pi*, %s)\n", str->s );
	char *s;
	t_str str2;

	++pi->line;
	fstr_init(&str2, 0);
	while (ANSI_OSMENAJ_isalnum(*pi->line))
	{
		fstr_add_char(&str2, *pi->line);
		++pi->line;
	}
	--pi->line;
	fprintf( tracciato, "...token_dollar()str2.s: %s\n", str->s );
	s = getenv(str2.s);
	if (s)
	{
		while (*s)
		{
			fstr_add_char(str, *s);
			++s;
		}
		pi->state = word;
	}
	fstr_destroy(&str2);
}

int token_error_quotes(char *line)
{
	fprintf( tracciato, "token_error_quotes(%s)\n", line );
	while (*line)
	{
		if (*line == 34 && *line)
		{
			line++;
			while (*line != 34 && *line)
				line++;
			if (!*line)
				return (1);
			line++;
		}
		else if (*line == 39 && *line)
		{
			line++;
			while (*line != 39 && *line)
				line++;
			if (!*line)
				return (1);
			line++;
		}
		else if (*line != 34 && *line != 39)
			line++;
	}
	return (0);
}

void token_great(t_pi *pi, t_str *str)
{
	fprintf( tracciato, "token_great(t_pi*, %s)\n", str->s );
	if (str->s[0])
	{
		fstr_add_char(str, '\0');
		fvec_add_str(pi->v, str);
		fstr_reset(str);
	}
	if ('>' == pi->line[1])
		pi->state = greatgreat;
	else
		pi->state = great;
	fstr_add_char(str, *pi->line);
	if (greatgreat == pi->state)
		fstr_add_char(str, *++pi->line);
	fstr_add_char(str, '\0');
	fvec_add_str(pi->v, str);
	fstr_reset(str);
}

void token_less(t_pi *pi, t_str *str)
{
	fprintf( tracciato, "token_less(t_pi*, %s)\n", str->s );
	if (str->s[0])
	{
		fstr_add_char(str, '\0');
		fvec_add_str(pi->v, str);
		fstr_reset(str);
	}
	if ('<' == pi->line[1])
		pi->state = lessless;
	else
		pi->state = less;
	fstr_add_char(str, *pi->line);
	if (lessless == pi->state)
		fstr_add_char(str, *++pi->line);
	fstr_add_char(str, '\0');
	fvec_add_str(pi->v, str);
	fstr_reset(str);
}

/*
Logic:
	read a char in 'c';
	if c == accceptable
		set word ?
		add c to existing t_str
	if c == space
		if double_quotes or single_quotes is set
			add c to existing t_str
		else
			set space
			close t_str
			add t_str to t_vec
			reset t_str
	if c == single_quotes
		if single_quotes is set
			close t_str
			add t_str to t_vec
			reset t_str
			add c to t_str
			close t_str
			add t_str to t_vec
			reset t_str
		if double_quotes is set
			add c to existing t_str
		else
			set single_quotes
			add c to existing t_str
	if c == single_quotes
		if single_quotes is set
			error ?
		if double_quotes is set
			add c to existing t_str
		else
			set single_quotes
			add c to existing t_str
			close t_str
			add t_str to t_vec
			reset t_str

*/
void token_pars_03(char *line, t_vec *vec)
{
	fprintf( tracciato, "token_pars_03(%s, t_vec*)\n", line );
	int		i;
	t_str	str;
	t_pi	pi;

	i = 0;
	while (line[i] && my_isspace(line[i]))
		++i;
	fstr_init(&str, 0);
	pi.v = vec;
	pi.line = line;
	pi.state = other;
	while (*pi.line)
	{
		if ('"' == *pi.line || '\'' == *pi.line)
			token_quotes(&pi, &str);
		else if (ANSI_OSMENAJ_isalnum(*pi.line))
			token_word(&pi, &str);
		else if (my_isspace(*pi.line))
			token_space(&pi, &str);
		else if ('<' == *pi.line)
			token_less(&pi, &str);
		else if ('>' == *pi.line)
			token_great(&pi, &str);
		else if ('|' == *pi.line)
			token_pipe(&pi, &str);
		else if ('$' == *pi.line)
			token_dollar(&pi, &str);
		++pi.line;
	}
	if (pi.state == word)
	{
		fstr_add_char(&str, '\0');
		fvec_add_str(pi.v, &str);
		fstr_reset(&str);
	}
	free(line);
	fstr_destroy(&str);
}

void token_pipe(t_pi *pi, t_str *str)
{
	if (str->s[0])
	{
		fstr_add_char(str, '\0');
		fvec_add_str(pi->v, str);
		fstr_reset(str);
	}
	pi->state = pipes;
	fstr_add_char(str, *pi->line);
	fstr_add_char(str, '\0');
	fvec_add_str(pi->v, str);
	fstr_reset(str);
}

// $ se la variabile non esiste il contenuto dal $ a separatore (spazio) o fine
// stringa viene ignorato
void token_quotes(t_pi *pi, t_str *str)
{
	fprintf( tracciato, "token_quotes(t_pi*, %s)\tpi->line: %s\n", str->s, pi->line );
	if (*pi->line == '"')
		pi->state = dq;
	else 
		pi->state = sq;
	while (*++pi->line)
	{
		if ('$' == *pi->line && dq == pi->state)
		{
			token_dollar(pi, str);
			++pi->line;
			pi->state = dq;
		}
		if (('"' == *pi->line && pi->state == dq) ||
			('\'' == *pi->line && pi->state == sq))
			break;
		else
			fstr_add_char(str, *pi->line);
	}
	pi->state = word;
}

void token_space(t_pi *pi, t_str *str)
{
	fprintf( tracciato
			, "token_space(t_pi*, t_str*)\tpi->line: %s; str->s %s\n"
			, pi->line, str->s );
	if (str->s[0])
	{
		fstr_add_char(str, '\0');
		fvec_add_str(pi->v, str);
		fstr_reset(str);
	}
}

void token_word(t_pi *pi, t_str *str)
{
	fprintf( tracciato
			, "token_word(t_pi*, t_str*)\tpi->line: %s; str->s %s\n"
			, pi->line, str->s );
	fstr_add_char(str, *pi->line);
	pi->state = word;
}
