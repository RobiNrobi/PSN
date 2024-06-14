#ifndef TOKEN_MAN_C
#define TOKEN_MAN_C

#include "parser_man.h"
#include "fvec_man.h"
#include "utility.h"
#include "../_extra.h"
// #include <readline/readline.h>
// #include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

void	quotes_man(char *line, int *p, t_str *str);
void	less_man(char *line, int *p, t_str *str, t_vec *vec);
void	great_man(char *line, int *p, t_str *str, t_vec *vec);
void	pipe_man(char *line, int *p, t_str *str, t_vec *vec);
void	space_man(t_str *str, t_vec *vec);
void	word_man(char *line, int *p, t_str *str);
void	dollar_man(char *line, int *p, t_str *str);
int		error_quotes(char *line);

#endif