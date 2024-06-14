#include "utility.h"

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int my_isalnum(int ch)
{
	fprintf( tracciato, "my_isalnum(%c)\n", (char)ch );
	if (!my_isspace(ch) && ch != '<' && ch != '>' && ch != '|'
			&& ch != '"' && ch != '\'' && ch != '$')
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

void	*my_calloc(size_t num, size_t size)
{
	void	*p;

	p = malloc(size * num);
	if (!p)
		return (NULL);
	p = my_memset(p, '\0', size * num);
	return (p);
}


void *my_memset(void *dest, int ch, size_t count)
{
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

