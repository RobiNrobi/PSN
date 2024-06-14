#ifndef PARSER_MAN_H
#define PARSER_MAN_H

#include "fvec2_man.h"

int		pars_get_words_seq(t_vec *vec, char *line, char *envp[]);
int		pars_parsline(char *line, char *envp[]);
void	pars_03(char *line, t_vec *vec, t_str str);
void	close_laststr(t_str *str, t_vec *vec);

#endif // PARSER_MAN_H
