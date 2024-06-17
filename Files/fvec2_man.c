#include "fvec2_man.h"
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
	// if (vec2->size == vec2->capacity)
	// 	if (!fvec2_double_cap(vec2))
	// 		return (0);
	if (!fvec_copy_to_new(&vec2->tvec[vec2->size], vec))
		return (0);
	// if (!fvec_copy(&vec2->tvec[vec2->size], vec))
	// 	return (0);
	++vec2->size;
	return (1);
}

void	fvec2_destroy(t_vec2 *vec2)
{
	fprintf( tracciato, "fvec2_destroy(t_vec2*)\n" );
	int i;

	if (!vec2)
		return ;
	if (!vec2->tvec)
		return ;
	i = vec2->size - 1;
	while (0 < i)
	{
		if(&vec2->tvec[i])
			fvec_destroy(&vec2->tvec[i]);
		--i;
	}
	fvec_destroy(vec2->tvec);
	free(vec2->tvec);
	vec2->tvec = NULL;
}

// int fvec2_double_cap(t_vec2 *vec2)
// {
// 	fprintf( tracciato, "fvec2_double_cap(t_vec2*)\n" );
// 	int		i;
// 	t_vec	*copy;

// 	vec2->capacity *= 2;
// 	copy = malloc(sizeof(t_vec) * (size_t)vec2->capacity);
// 	if (!copy)
// 		return (0);
// 	i = 0;
// 	while (vec2->size > i)
// 	{
// 		fvec_init(&copy[i], vec2[i].capacity);
// 		fvec_copy(&copy[i], &vec2->tvec[i]);
// 		++i;
// 	}
// 	free(vec2->tvec);
// 	vec2->tvec = copy;
// 	return (1);
// }

int fvec2_init(t_vec2 *vec2, int cap)
{
	fprintf( tracciato, "fvec2_init(t_vec2*)\n" );
	if (1 > cap)
		cap = DEFAULT_VEC2_SIZE;
	vec2->size = 0;
	vec2->capacity = cap;
	// vec2->tvec = malloc(sizeof(t_vec) * (size_t)(vec2->capacity));
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
