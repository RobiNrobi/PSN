#include "token_man.h"

void word_man(char *line, int *p, t_str *str)
{
	int i;

	i = *p;
	fstr_add_char(str, line[i]);
	str->state = word;
}
void dollar_man(char *line, int *p, t_str *str)
{
	int j;
	char *s;
	t_str str2;

	*p += 1;
	j = 0;
	fstr_init(&str2, 0);
	while (my_isalnum(line[*p]) && line[*p])
	{
		fstr_add_char(&str2, line[*p]);
		*p += 1;
	}
	*p -= 1;
	s = getenv(str2.s);
	if (s)
	{
		while (s[j])
		{
			fstr_add_char(str, s[j]);
			j++;
		}
		str->state = word;
	}
	fstr_destroy(&str2);
}

int error_quotes(char *line)
{
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

