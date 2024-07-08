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
void	fvec2_deep_copy(t_vec2 *v2, char const *const *const s);
void	fvec2_destroy(t_vec2 *vec2);
int		fvec2_double_cap(t_vec2 *vec2);
t_vec	*fvec2_find_tvec_by_charp(t_vec2 *v2, char const *const s);
int		fvec2_init(t_vec2 *vec2, int cap);
char	**fvec2_turn_into_charpp(t_vec2 *v2, char*** s);

// TODO: delete the following:
// Temporary / debug functions:
void	fvec2_print_vec2(t_vec2 *vec2);		// for DEBUG only
// char	**fvec2_expose_as_charpp(t_vec2 *vec2, char*** s);
// int		fvec2_shallow_copy(t_vec2 *v2, char **s); no more needed + dangerous
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#endif // FVEC2_MAN_H
