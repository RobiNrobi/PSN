#ifndef PARSER_MAN_H
#define PARSER_MAN_H

#include "fvec_man.h"
#include "fvec2_man.h"

void 	pars_check_syntax(t_vec2 *cmds);
int		pars_expand_vars(t_vec *vec);
int		pars_get_words_seq(t_vec *vec, char *line);
void	pars_pars_on_pipes(t_vec *tv, char *line);
int 	pars_parsline(char *line, t_vec2 *cmds);

#endif // PARSER_MAN_H
