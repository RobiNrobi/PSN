#ifndef UTILITY_H
#define UTILITY_H

/*
** stdlib.h needed for size_t
*/
#include <stdlib.h>

int		ANSI_OSMENAJ_isalnum(int ch);
int		is_bash_metachar(int ch);
void	*my_calloc(size_t num, size_t size);
int		my_isalnum(int ch);
int		my_isalpha(int ch);
int		my_isdigit(int ch);
int		my_islower(int ch);
int		my_isspace(int ch);
int		my_isupper(int ch);
void	*my_memset(void *dest, int ch, size_t count);
int		my_strlen(char const *const s);

#endif // UTILITY_H

/*
int my_iscntrl(int ch);
int my_isgraph(int ch);
int my_isblank(int ch);
int my_isprint(int ch);
int my_ispunct(int ch);
*/
