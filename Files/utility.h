#ifndef UTILITY_H
#define UTILITY_H

/*
** stdlib.h needed for size_t
*/
#include <stdlib.h>
#include "minishell.h"
#include "fvec_man.h"
#include "fstr_man.h"

int		my_isalnum(int ch);
int		my_isspace(int ch);
void	*my_calloc(size_t num, size_t size);
void	*my_memset(void *dest, int ch, size_t count);



#endif // UTILITY_H
