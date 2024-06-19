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

int is_any_of(int ch, char const * const s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)ch)
			return (1);
		++i;
	}
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

/*
** Emulate strcmp() from the standard library <string.h>
** From man strcmp:
** int strcmp(const char *s1, const char *s2)
** ...compares the two strings s1 and s2... The comparison is done using
** unsigned characters.
** strcmp() returns an integer indicating the result of the comparison, as
** follows:
** • 0, if the s1 and s2 are equal;
** • a negative value if s1 is less than s2;
** • a positive value if s1 is greater than s2.
*/
int my_strcmp(char const *const s1, char  const* const s2)
{
	fprintf( tracciato, "my_strcmp(%s, %s)\n", s1, s2 );
	unsigned char	ss1;
	unsigned char	ss2;
	int				i;

	if (!s1 | !s2)
		return (0);
	i = 0;
	ss1 = (unsigned char)s1[i];
	ss2 = (unsigned char)s2[i];
	while (s1[i] && s2[i])
	{
		ss1 = (unsigned char)s1[i];
		ss2 = (unsigned char)s2[i];
		if (ss1 != ss2)
			return (ss1 - ss2);
		++i;
	}
	return (ss1 - ss2);
}

char *my_strjoin(char const *const s1, char  const* const s2)
{
	fprintf( tracciato, "my_strjoin(%s, %s)\n", s1, s2 );
	char	*tot;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	tot = malloc(sizeof(char) * (size_t)(my_strlen(s1) + my_strlen(s2) + 1));
	i = 0;
	while (s1[i])
	{
		tot[i] = s1[i];
		++i;
	}
	k = 0;
	while (s2[k])
		tot[i++] = s2[k++];
	tot[i] = '\0';
	fprintf( tracciato, "...my_strjoin()\tAbout to return: %s\n", tot );
	return (tot);
}
