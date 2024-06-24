#ifndef TOKEN_MAN_C
#define TOKEN_MAN_C

#include "fvec_man.h"

typedef struct s_pars_info
{
	t_vec	*v;
	char	*line;
}	t_pai;

void	token_dollar(t_pai *pi, t_str *str);
int		token_error_quotes(char *line);
void	token_great(t_pai *pi, t_str *str);
void	token_less(t_pai *pi, t_str *str);
void	token_pars_03(char *line, t_vec *vec);
void	token_pipe(t_pai *pi, t_str *str);
void	token_quotes(t_pai *pi, t_str *str);
void	token_space(t_pai *pi, t_str *str);
void	token_word(t_pai *pi, t_str *str);

#endif
