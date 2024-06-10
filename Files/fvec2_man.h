#ifndef FVEC2_MAN_H
#define FVEC2_MAN_H

#include "fvec_man.h"

#ifndef DEFAULT_VEC2_SIZE
# define DEFAULT_VEC2_SIZE 15
#endif

typedef struct s_fvec2
{
	int		size;
	int		capacity;
	t_vec	*tvec;
}	t_vec2;

int		fvec2_add_vec(t_vec2 *vec2, t_vec* vec);
void	fvec2_destroy(t_vec2 *vec2);
int		fvec2_double_cap(t_vec2 *vec2);
int		fvec2_init(t_vec2 *vec2, int cap);
void	fvec2_print_vec2(t_vec2 *vec2);		// for DEBUG only

#endif // FVEC2_MAN_H
