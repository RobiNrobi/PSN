#include "fstr_man.h"
#include "utility.h"
#include <stdlib.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void fstr_add_char(t_str *str, char c)
{
	fprintf( tracciato, "fstr_add_char(t_str*, %c)\n", c );
	if (!str->capacity)
		fstr_init(str, 0);
	if (str->size == str->capacity)
		fstr_double_cap(str);
	str->s[str->size] = c;
	++str->size;
}

int fstr_copy(t_str *dest, t_str const * const orig)
{
	fprintf( tracciato, "fstr_copy(s_str*, %s)\n", orig->s );
	int i;

	if (!dest || !orig)
		return (0);
	dest->capacity = orig->capacity;
	dest->size = orig->size;
	i = 0;
	while (dest->capacity > i)
	{
		// fprintf( tracciato
		// 		, "...fstr_copy()\tcopying orig[%d]: %c into dest[%d]\n"
		// 		, i, orig->s[i], i );
		dest->s[i] = orig->s[i];
		++i;
	}
	return (1);
}

int fstr_copy_to_new(t_str *dest, const t_str * const orig)
{
	fprintf( tracciato, "fstr_copy_to_new(s_str*, %s)\n", orig->s );
	int i;

	if (!dest || !orig)
		return (0);
	dest->capacity = orig->capacity;
	dest->size = orig->size;
	dest->state = orig->state;
	dest->s = malloc(sizeof(char) * (size_t)orig->capacity);
	i = 0;
	while (dest->capacity > i)
	{
		// fprintf( tracciato
		// 		, "...fstr_copy()\tcopying orig[%d]: %c into dest[%d]\n"
		// 		, i, orig->s[i], i );
		dest->s[i] = orig->s[i];
		++i;
	}
	return (1);
}

void fstr_destroy(t_str *str)
{
	fprintf( tracciato, "fstr_destroy(t_str*)\n" );
	if (str)
	{
		str->capacity = 0;
		str->size = 0;
		if (str->s)
		{
			free(str->s);
			str->s = NULL;
		}
		str = NULL;
	}
}

void fstr_double_cap(t_str *str)
{
	fprintf( tracciato, "fstr_double_cap(t_str*)\n" );
	int		i;
	char	*copy;

	if (!str)
		return ;
	str->capacity *= 2;
	copy = malloc(sizeof(char) * (size_t)str->capacity);
	i = 0;
	while (str->size > i)
	{
		copy[i] = str->s[i];
		++i;
	}
	while (str->capacity > i)
	{
		copy[i] = '\0';
		++i;
	}
	free(str->s);
	str->s = copy;
}

char *fstr_init(t_str *str, int cap)
{
	fprintf( tracciato, "fstr_init(t_str*, %d)\n", cap );
	if (1 > cap)
		cap = DEFAULT_STR_SIZE;
	str->size = 0;
	str->capacity = cap;
	// str->s = malloc(sizeof(char) * (size_t)(cap));
	str->s = my_calloc((size_t)(cap), sizeof(char));
	// if (str->s)
	// 	fstr_init_els(str);
	return (str->s);
}

void fstr_init_els(t_str *str)
{
	fprintf( tracciato, "fstr_init_els(t_str*)\n" );
	int	i;

	if (str && str->s)
	{
		i = 0;
		while (str->capacity > i)
		{
			str->s[i] = '\0';
			++i;
		}
	}
}

void fstr_print_str(t_str *str)
{
	fprintf( tracciato, "fstr_print_str(%s)\n", str->s );
	int i;

	if (!str)
		return ;
	i = 0;
	while (str->size > i)
	{
		printf("%c", str->s[i]);
		++i;
	}
}

/*
** fstr_reset() set all the chars in str->s to \0 and str->size to 0, actually
**              letting str ready to be used again as if it has just been
**              initialized (apart from the capacity value).
** returns 0 in case of error, which is extremely unlikely, unless it is invoked
**         passing an uninitialized t_str*. Otherwise returns 1.
*/
int fstr_reset(t_str *str)
{
	fprintf( tracciato, "fstr_reset(%s)\n", str->s );
	int i;

	if (!str || !str->s)
		return (0);
	i = 0;
	while (str->size > i)
	{
		str->s[i] = '\0';
		++i;
	}
	str->size = 0;
	return (1);
}
