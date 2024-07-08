#include "fvec2_man.h"
// #include "tmp_utils.h"
#include "utility.h"
#include <stdlib.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int fvec2_add_vec(t_vec2 *vec2, t_vec *vec)
{
	fprintf( tracciato, "fvec2_add_vec(t_vec2*, t_vec*)\n" );
	if (!vec2 || !vec || !vec2->capacity)
		return (0);
	if (vec2->size == vec2->capacity)
		if (!fvec2_double_cap(vec2))
			return (0);
	if (!fvec_copy_to_new(&vec2->tvec[vec2->size], vec))
		return (0);
	++vec2->size;
	return (1);
}

/*
** fvec2_deep_copy() second parameter is supposed to be a pointer to a sequence
** of C-style strings without spaces inside and at least a '=', like so:
** s[0] --> "something_left=something_right"
** s[1] --> "something_else_left=something_else_right"
** ...
** s[n] --> NULL
** The first paramter will be filled with a sequence of t_vec storing exactly
** two t_str contyaining a copy of the above C-style strings splitted at the
** '=', like so:
** t_vec2
**     --> t_vec
**         --> t_str --> "something_left"
**         --> t_str --> "something_right"
**     --> t_vec
**         --> t_str --> "something_else_left"
**         --> t_str --> "something_else_right"
**     ...
** Memory will be copied so that the above two variables will be independent
** from each other.
*/
void fvec2_deep_copy(t_vec2 *v2, char const *const *const s)
{
	fprintf( tracciato, "fvec2_deep_copy(t_vec2*, char**)\n" );
	t_vec	v;
	t_str	ts;
	int		i;
	int		k;

	fvec_init(&v, 0);
	fstr_init(&ts, 0);
	i = 0;
	while (s && s[i])
	{
		k = 0;
		while (s[i][k] && '=' != s[i][k])
		{
			fstr_add_char(&ts, s[i][k]);
			++k;
		}
		fvec_close_add_str(&v, &ts);
		fstr_reset(&ts);
		++k;
		while (s[i][k])
		{
			fstr_add_char(&ts, s[i][k]);
			++k;
		}
		fvec_close_add_str(&v, &ts);
		fvec2_add_vec(v2, &v);
		fvec_reset(&v);
		fstr_reset(&ts);
		++i;
	}
	fstr_destroy(&ts);
	fvec_destroy(&v);
}

void	fvec2_destroy(t_vec2 *vec2)
{
	fprintf( tracciato, "fvec2_destroy(t_vec2*)\n" );
	int i;

	if (!vec2 || !vec2->tvec)
		return ;
	i = vec2->capacity - 1;
	while (0 < i)
	{
		fvec_destroy(&vec2->tvec[i]);
		--i;
	}
	fvec_destroy(vec2->tvec);
	free(vec2->tvec);
	vec2->tvec = NULL;
}

int fvec2_double_cap(t_vec2 *vec2)
{
	fprintf( tracciato, "fvec2_double_cap(t_vec2*)\n" );
	int		i;
	t_vec	*copy;

	vec2->capacity *= 2;
	copy = my_calloc((size_t)vec2->capacity, sizeof(t_vec));
	if (!copy)
		return (0);
	i = 0;
	while (vec2->size > i)
	{
		fvec_init(&copy[i], vec2->tvec[i].capacity);
		fvec_copy(&copy[i], &vec2->tvec[i]);
		fvec_destroy(&vec2->tvec[i]);
		++i;
	}
	free(vec2->tvec);
	vec2->tvec = copy;
	return (1);
}

t_vec *fvec2_find_tvec_by_charp(t_vec2 *v2, char const *const s)
{
	fprintf( tracciato, "fvec2_find_tvec_by_charp(t_vec2*, char*)\n" );
	int		i;
	t_vec	*p;

	if (!v2 || !s)
		return (NULL);
	i = 0;
	while (v2->size > i)
	{
		p = &v2->tvec[i];
		if (!my_strcmp(p->tstr[0].s, s))
			return (p);
		++i;
	}
	return (NULL);
}

int fvec2_init(t_vec2 *vec2, int cap)
{
	fprintf( tracciato, "fvec2_init(t_vec2*)\n" );
	if (1 > cap)
		cap = DEFAULT_VEC2_SIZE;
	vec2->size = 0;
	vec2->capacity = cap;
	vec2->tvec = my_calloc((size_t)(vec2->capacity), sizeof(t_vec));
	if (!vec2->tvec)
		return (0);
	return (1);
}

void fvec2_print_vec2(t_vec2 *vec2)
{
	fprintf( tracciato, "fvec2_print_vec2(t_vec2*)\n" );
	printf( "Fake 2D vector content\n----------------------\n" );
	for (int i = 0; vec2->size > i; ++i) {
		printf ( "Inner tvec %d --> ", i );
		fvec_print_vec(&vec2->tvec[i]);
	}
}

/*
** cfr. fvec2_deep_copy()
*/
// char **fvec2_expose_as_charpp(t_vec2 *vec2, char ***s)
// {
// 	fprintf( tracciato, "fvec2_expose_as_charpp(t_vec2*, char***)\n" );
// 	int i;
// 	int	howmany;
// 	int k;

// 	i = 0;
// 	howmany = vec2->size;
// 	while (vec2->size > i)
// 	{
// 		howmany += vec2->tvec[i].size;
// 		++i;
// 	}
// 	*s = my_calloc((size_t)(howmany + 1), sizeof(char**));
// 	(*s)[howmany] = NULL;
// 	i = 0;
// 	while (vec2->size > i)
// 	{
// 		k = 0;
// 		while (vec2->tvec[i].size > k)
// 		{
// 			(*s)[i + k] = vec2->tvec[i].tstr[k].s;
// 			++k;
// 		}
// 		++i;
// 	}
// 	return (*s);
// }

/*
** Dangerous and no more needed fuunction()!
*/
// int fvec2_shallow_copy(t_vec2 *v2, char **s)
// {
// 	fprintf( tracciato, "fvec2_shallow_copy(t_vec2**, char**)\n" );
// 	int i;
// 	int k;

// 	if (!s || !*s)
// 		return (0);
// 	fvec2_init(v2, count_elem_in_charpp(s));
// 	printf( "fvec2_shallow_copy() --> v2->capacity: %d\n", v2->capacity );
// 	i = 0;
// 	while (v2->capacity > i)
// 	{
// 		if (!s[i] || !&v2[i])
// 		{
// 			printf( "\ni: %d; v2->size: %d\n", i, v2->size );
// 			exit(EXIT_FAILURE);
// 		}
// 		// (*v2)->tvec[i] = malloc(sizeof(t_vec));
// 		v2->tvec[i].size = 2;
// 		v2->tvec[i].capacity = 2;
// 		v2->tvec[i].tstr = malloc(sizeof(t_str) * 2);
// 		v2->tvec[i].tstr[0].s = s[i];
// 		k = 0;
// 		while (s[i][k] && '=' != s[i][k])
// 			++k;
// 		v2->tvec[i].tstr[0].size = k;
// 		v2->tvec[i].tstr[0].capacity = my_strlen(s[i]) + 1;
// 		v2->tvec[i].tstr[1].s = &s[i][++k];
// 		v2->tvec[i].tstr[1].size = v2->tvec[i].tstr[0].capacity - v2->tvec[i].tstr[0].size - 1;
// 		v2->tvec[i].tstr[1].capacity = v2->tvec[i].tstr[1].size;
// 		++i;
// 	}
// 	v2->size = i;
// 	printf( "fvec2_shallow_copy() --> v2->size: %d\n", v2->size );
// 	return (1);
// }

/*
** fvec_turn_into_charpp() takes as first parameter a t_vec2 which is supposed
** to be composed like so:
** t_vec2
**     --> t_vec
**         --> t_str[0]
**         --> t_str[1]
**     --> t_vec
**         --> t_str[0]
**         --> t_str[1]
**     ...
** i.e. every pointed t_vec is supposed to point to exactly two t_str.
** The t_vec2 is turned into a char** assembled according to this logic:
** t_vec2               <---> char**
**     --> t_vec                char* --> t_str[0].s + '=' + t_str[1].s
**         --> t_str[0]
**         --> t_str[1]
**     --> t_vec                char* --> t_str[0].s + '=' + t_str[1].s
**         --> t_str[0]
**         --> t_str[1]
** In words: the two strings pointed by the two t_str inside each t_vec are
**           joined together, having a '=' between them.
**           So each t_vec (or every couple of t_str, according to your own
**           point of view) becomes a char*.
**           The t_vec2 itself becomes a char** which holds each of the above
**           char*.
**           The second parameter (char***) will point to this last char**.
** All the memory is copied, so that the passed t_vec2 and char*** are totally
** indipenent.
*/
char **fvec2_turn_into_charpp(t_vec2 *v2, char ***s)
{
	fprintf( tracciato, "fvec_turn_into_charpp(t_vec2*, char***)\n" );
	*s = my_calloc((size_t)(v2->size + 1), sizeof(char**));
	int i = 0;
	while (v2->size > i)
	{
		int length = v2->tvec[i].tstr[0].size + v2->tvec[i].tstr[1].size + 2;
		(*s)[i] = my_calloc((size_t)length, sizeof(char));
		my_strcpy((*s)[i], v2->tvec[i].tstr[0].s);
		(*s)[i][v2->tvec[i].tstr[0].size] = '=';
		my_strcpy(&(*s)[i][v2->tvec[i].tstr[0].size + 1], v2->tvec[i].tstr[1].s);
		// TODO: remove the folloowing instruction:
		printf( "%s\n", (*s)[i]);
		// ^^^^^^^^^^^^^^^^^^^^^^
		++i;
	}
	(*s)[i] = NULL;
	return (*s);
}
