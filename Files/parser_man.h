#ifndef PARSER_MAN_H
#define PARSER_MAN_H

#include "fvec_man.h"
// #include "fvec2_man.h"

int		pars_expand_var(t_vec *vec, int ind, int ch);
int		pars_expand_vars(t_vec *vec);
int		pars_get_words_seq(t_vec *vec, char *line);
int		pars_parsline(char *line);
void	pars_pars_on_pipes(t_vec *tv, char *line);

#endif // PARSER_MAN_H
