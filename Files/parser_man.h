#ifndef PARSER_MAN_H
#define PARSER_MAN_H

#include "fvec2_man.h"

t_vec	*pars_char_by_char(t_vec *vec, char *str);
t_vec	*pars_get_words_seq(t_vec *vec, char *str);
int		pars_parsline(char *line);
char	*pars_skip_spaces(char *str);

int		pars_getword(char *line, t_str *str);
int 	lexer(char *line, t_vec2 *vec2);
int		pars_03(char *line, t_vec2 *vec2);


#endif // PARSER_MAN_H
