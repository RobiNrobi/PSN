#ifndef PARSER_MAN_H
#define PARSER_MAN_H

#include "fvec_man.h"

int		pars_expand_var(t_vec *vec, int ind, int ch);
int		pars_expand_vars(t_vec *vec);
int		pars_get_words_seq(t_vec *vec, char *line);
int		pars_parsline(char *line);
void	close_laststr(t_str *str, t_vec *vec);

#endif // PARSER_MAN_H
