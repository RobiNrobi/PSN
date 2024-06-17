#include "utility.h"

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int ANSI_OSMENAJ_isalnum(int ch)
{
	fprintf( tracciato, "ANSI_OSMENAJ_isalnum(%c)\n", (char)ch );
	if (!my_isspace(ch) && ch != '<' && ch != '>' && ch != '|'
		&& ch != '"' && ch != '\'' && ch != '$')
		return (1);
	return (0);
}

/*
** According to the Bash reference manual, a metacharacter is:
** a character that, when unquoted, separates words. A metacharacter is a
** space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’,
**  ‘)’, ‘<’, or ‘>’.
*/
int is_bash_metachar(int ch)
{
	fprintf( tracciato, "is_bash_metachar(%c)\n", (char)ch );
	int			i;
	int			length;
	const char	s[] = " \t\n|&;()<>";

	i = 0;
	length = (int)(sizeof(s) / sizeof(s[0]));
	while (length > i)
	{
		if (s[i] == (char)ch)
			return (1);
		++i;
	}
	return (0);
}

void	*my_calloc(size_t num, size_t size)
{
	fprintf( tracciato, "my_calloc(%lu, %lu)\n", num, size );
	void	*p;

	p = malloc(size * num);
	if (!p)
		return (NULL);
	p = my_memset(p, '\0', size * num);
	return (p);
}

int my_isalnum(int ch)
{
	fprintf( tracciato, "my_isalnum(%c)\n", (char)ch );
	if (my_isalpha(ch) || my_isdigit(ch))
		return (1);
	return (0);
}

int my_isalpha(int ch)
{
	fprintf( tracciato, "my_isalpha(%c)\n", (char)ch );
	if (my_isupper(ch) || my_islower(ch))
		return (1);
	return (0);
}

int my_isdigit(int ch)
{
	fprintf( tracciato, "my_isdigit(%c)\n", (char)ch );
	if ('0' <= ch && ch <= '9')
		return (1);
	return (0);
}

int my_islower(int ch)
{
	fprintf( tracciato, "my_islower(%c)\n", (char)ch );
	if ('a' <= ch && ch <= 'z')
		return (1);
	return (0);
}

int my_isspace(int ch)
{
	fprintf( tracciato, "my_isspace(%c)\n", (char)ch );
	int			i;
	int			length;
	const char	s[] = "\t\n\v\f\r ";

	i = 0;
	length = (int)(sizeof(s) / sizeof(s[0]));
	while (length > i)
	{
		if (s[i] == (char)ch)
			return (1);
		++i;
	}
	return (0);
}

int my_isupper(int ch)
{
	fprintf( tracciato, "my_isupper(%c)\n", (char)ch );
	if ('A' <= ch && ch <= 'Z')
		return (1);
	return (0);
}

void *my_memset(void *dest, int ch, size_t count)
{
	fprintf( tracciato, "my_memset(void*, %d, %lu)\n", ch, count );
	unsigned char	uc;
	size_t			i;
	unsigned char	*p;

	uc = (unsigned char)ch;
	p = (unsigned char*)dest;
	i = 0;
	while (count > i)
		p[i++] = uc;
	return (dest);
}

int my_strlen(char const *const s)
{
	fprintf( tracciato, "my_strlen(%s)\n", s );
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}
