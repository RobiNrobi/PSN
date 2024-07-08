#include "utility.h"
#include <errno.h>			// TODO: remove if errno not set in strdup
#include <stdlib.h>

#include <unistd.h>

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

void display_error(char *s)
{
	fprintf( tracciato, "display_error(%s)\n", s );
	int i;

	i = my_strlen(s);
	// WARNING: Possiamo usare sia printf() che perror()...
	write(2, s, (size_t)i);
	write(1, "\n", 1);
}

void display_error_syntax(char *s)
{
	fprintf( tracciato, "display_error_syntax(%s)\n", s );
	// WARNING: Possiamo usare sia printf() che perror()...
	write(2, "Syntax error near unexpected token ", 36);
	write(2, "'", 1);
	write(2, s, 2);
	write(2, "'", 1);
	write(1, "\n", 1);
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
/*
** emulates memcpy() from <string.h>
** From man memcpy():
** ------------------
** void *memcpy(void dest[restrict .n], const void src[restrict .n], size_t n);
** The memcpy() function copies n bytes from memory area src to  memory area
** dest.
** The memory areas must not overlap.
** Use memmove(3) if the memory areas do overlap.
** From https://en.cppreference.com/w/c/string/byte/memcpy :
** ---------------------------------------------------------
** Copies count characters from the object pointed to by src to the object
** pointed to by dest.
** Both objects are interpreted as arrays of unsigned char.
** The behavior is undefined if access occurs beyond the end of the dest array.
** If the objects overlap, the behavior is undefined.
** The behavior is undefined if either dest or src is an invalid or null
** pointer.
** Returns a copy of dest.
*/
void	*my_memcpy(void *dest, const void *src, int n)
{
	fprintf( tracciato, "my_memcpy(void*, void*, %d)\n", n );
	int	i;

	if (!dest || !src)
		return (0);
	i = 0;
	while (n > i)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
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

/*
** emulates strcpy() from string.h
** From man strcpy
** ---------------
** char *strcpy(char *restrict dst, const char *restrict src);
** These functions copy the string pointed to by src, into a string at the
** buffer pointed to by dst.
** The programmer is responsible for allocating a destination buffer large
** enough, that is, strlen(src) + 1.
** These functions return dst.
*/
char *my_strcpy(char *dest, const char *src)
{
	fprintf( tracciato, "my_strcpy(%s, %s)\n", dest, src );
	int i;

	if (!dest || !src)
		return (dest);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

/*
** emulates strdup() from string.h
** From man strdup:
** ---------------
** char *strdup(const char *s);
** The strdup() function returns a pointer to a new string which is a duplicate
** of the string s.
** Memory for the new string is obtained with malloc(), and can be freed with
** free().
** On success, the strdup() function returns a pointer to the duplicated string.
** It returns NULL if insufficient memory was available, with errno set to
** indicate the error.
** ERRORS: ENOMEM Insufficient memory available to allocate duplicate string.

** From https://en.cppreference.com/w/c/string/byte/strdup :
** ---------------------------------------------------------
** Returns a pointer to a null-terminated byte string, which is a duplicate of
** the string pointed to by src.
** The space for the new string is obtained as if the malloc was invoked.
** The returned pointer must be passed to free to avoid a memory leak.
** If an error occurs, a null pointer is returned and errno might be set.
** Return value: A pointer to the newly allocated string, or a null pointer if
**               an error occurred.
*/
char	*my_strdup(const char *str)
{
	fprintf( tracciato, "my_strdup(%s)\n", str );
	int		nume;
	char	*cpy;

	nume = my_strlen(str) + 1;
	cpy = (char *)malloc((size_t)nume * sizeof(char));
	if (!cpy)
	{
		// WARNING: add the following to match strdup?
		errno = ENOMEM;
		// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		free(cpy);			// FIXME: you cannot free(NULL) !!!!
		return (NULL);
	}
	my_memcpy(cpy, str, nume);
	return ((char *)cpy);
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

int strcpy_up_to_char(char *s1, const char * const s2, char c)
{
	fprintf( tracciato, "strcpy_up_to_char(%s, %s, %c)\n", s1, s2, c );
	int	i;

	if (!s1 || !s2 || !*s2)
		return (0);
	i = 0;
	while (s2[i] && c != s2[i])
	{
		s1[i] = s2[i];
		++i;
	}
	return (i);
}
