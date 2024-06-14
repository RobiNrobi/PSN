#include "fvec_man.h"
#include "utility.h"
#include <stdlib.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int fvec_add_str(t_vec *vec, t_str *str)
{
	fprintf( tracciato, "fvec_add_str(t_vec*, %s)\n", str->s );
	if (!vec || !str || !vec->capacity)
		return (0);
	if (vec->size == vec->capacity)
		if (!fvec_double_cap(vec))
			return (0);
	if (!fstr_copy_to_new(&vec->tstr[vec->size], str))
		return (0);
	++vec->size;
	return (1);
}

int fvec_copy(t_vec *dest, t_vec *orig)
{
	fprintf( tracciato, "fvec_copy(t_vec*, t_vec*)\n" );
	int i;

	if (!dest || !orig)
		return (0);
	dest->capacity = orig->capacity;
	dest->size = orig->size;
	i = 0;
	while (dest->capacity > i)
	{
		fstr_init(&dest->tstr[i], orig->tstr[i].capacity);
		fstr_copy(&dest->tstr[i], &orig->tstr[i]);
		++i;
	}
	return (1);
}

int fvec_copy_to_new(t_vec *dest, t_vec *orig)
{
	fprintf( tracciato, "fvec_copy(t_vec*, t_vec*)\n" );
	int i;

	if (!dest || !orig)
		return (0);
	dest->capacity = orig->capacity;
	dest->size = orig->size;
	dest->env = orig->env;
	dest->tstr = my_calloc((size_t)dest->capacity, sizeof(t_str));
	i = 0;
	while (dest->capacity > i)
	{
		// fstr_init(&dest->tstr[i], orig->tstr[i].capacity);
		fstr_copy_to_new(&dest->tstr[i], &orig->tstr[i]);
		++i;
	}
	return (1);
}

void	fvec_destroy(t_vec *vec)
{
	fprintf( tracciato, "fvec_destroy(t_vec*)\n" );
	int i;

	if (!vec)
		return ;
	if (!vec->tstr)
		return ;
	i = vec->size - 1;
	while (0 < i)
	{
		if (&vec->tstr[i])
			if (vec->tstr[i].s)
				fstr_destroy(&vec->tstr[i]);
		--i;
	}
	fstr_destroy(&vec->tstr[i]);
	free(vec->tstr);
}

int fvec_double_cap(t_vec *vec)
{
	fprintf( tracciato, "fvec_double_cap(t_vec*)\n" );
	int		i;
	t_str	*copy;

	vec->capacity *= 2;
	copy = malloc(sizeof(t_str) * (size_t)vec->capacity);
	if (!copy)
		return (0);
	i = 0;
	while (vec->size > i)
	{
		fstr_init(&copy[i], vec[i].capacity);
		fstr_copy(&copy[i], &vec->tstr[i]);
		++i;
	}
	free(vec->tstr);
	vec->tstr = copy;
	return (1);
}

int	fvec_init(t_vec *vec, int cap, char **envp)
{
	fprintf( tracciato, "fvec_init(t_vec*)\n" );
	if (1 > cap)
		cap = DEFAULT_VEC_SIZE;
	vec->size = 0;
	vec->capacity = cap;
	vec->env = envp;
	// vec->tstr = malloc(sizeof(t_str) * (size_t)(vec->capacity));
	vec->tstr = my_calloc((size_t)(vec->capacity), sizeof(t_str));
	if (!vec->tstr)
		return (0);
	return (1);
}

// int fvec_reset(t_vec *vec)
// {
// 	fprintf( tracciato, "fvec_reset(t_vec*)\n" );
// 	if (!vec)
// 		return (0);
// 	fvec_destroy(vec);
// 	fvec_init(vec, 0);
// 	return (1);
// }

// Funzione per convertire l'enumerazione in una stringa
// Da cancellare
static const char* state_to_string(t_state state) {
    switch (state) {
        case dq: return "dq";
        case sq: return "sq";
        case less: return "less";
        case lessless: return "lessless";
        case great: return "great";
        case greatgreat: return "greatgreat";
        case pipes: return "pipe";
        case word: return "word";
        default: return "unknown";
    }
}

void fvec_print_vec(t_vec *vec)
{
	fprintf( tracciato, "fvec_print_vec(t_vec*)\n" );
	int i;

	printf( "tvec content:\n" );
	i = 0;
	while (vec->size > i)
	{
		printf( "\ttstr %2d: ", i );
		fstr_print_str(&vec->tstr[i]);
		printf("\tState: %s\n", state_to_string(vec->tstr[i].state));
		++i;
	}
	printf("\n");
}
