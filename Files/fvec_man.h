#ifndef FVEC_MAN_H
#define FVEC_MAN_H

#include "fstr_man.h"

#ifndef DEFAULT_VEC_SIZE
# define DEFAULT_VEC_SIZE 15
#endif

typedef struct s_fvec
{
	int		size;
	int		capacity;
	t_str	*tstr;
}	t_vec;

int		fvec_add_str(t_vec *vec, t_str* str);
int		fvec_copy(t_vec *dest, t_vec *orig);
int		fvec_copy_to_new(t_vec *dest, t_vec *orig);
void	fvec_destroy(t_vec *vec);
int		fvec_double_cap(t_vec *vec);
int		fvec_init(t_vec *vec, int cap);
int		fvec_reset(t_vec *vec);

void	fvec_print_vec(t_vec *vec);		// for DEBUG only

#endif // FVEC_MAN_H
