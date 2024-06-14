#include "token_man.h"

//TODO: remove the following
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// $ se la variabile non esiste il contenuto dal $ a separatore (spazio) o fine stringa viene ignorato

void quotes_man(char *line, int *p, t_str *str)
{
	int i;

	i = *p;
	if (line[i] == '"')
		str->state = dq;
	else 
		str->state = sq;
	while (line[++i])
	{
		if (('$' == line[i]) && str->state == dq)
		{
			dollar_man(line, &i, str);
			i++;
			str->state = dq;
		}
		if ((line[i] == '"' && str->state == dq) || (line[i] == '\'' && str->state == sq))
			break;
		else
			fstr_add_char(str, line[i]);
	}
	str->state = word;
	*p = i;
}

void less_man(char *line, int *p, t_str *str, t_vec *vec)
{
	int i;

	i = *p;
	if (str->s[0])
		close_laststr(str, vec);
	if ('<' != line[i + 1])
		str->state = less;
	else
		str->state = lessless;
	fstr_add_char(str, line[i]);
	if (line[i + 1] == '<')
		fstr_add_char(str, line[++i]);
	close_laststr(str, vec);
	*p = i;
}

void great_man(char *line, int *p, t_str *str, t_vec *vec)
{
	int i;

	i = *p;
	if (str->s[0])
		close_laststr(str, vec);
	if ('>' != line[i + 1])
		str->state = great;
	else
		str->state = greatgreat;
	fstr_add_char(str, line[i]);
	if (line[i + 1] == '>')
		fstr_add_char(str, line[++i]);
	close_laststr(str, vec);
	*p = i;
}

void pipe_man(char *line, int *p, t_str *str, t_vec *vec)
{
	int i;

	i = *p;
	if (str->s[0])
		close_laststr(str, vec);
	str->state = pipes;
	fstr_add_char(str, line[i]);
	close_laststr(str, vec);
}

void space_man(t_str *str, t_vec *vec)
{
	if (str->s[0])
		close_laststr(str, vec);
}
