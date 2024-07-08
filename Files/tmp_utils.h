#ifndef TMP_UTILS_H
#define TMP_UTILS_H

// #include "fvec2_man.h"
#include "fvec_man.h"

int		count_elem_in_charpp(char **s);
t_vec	*expand_path(t_vec *v);
void	free_charpp(char **ss);
int		is_quote_or_pipe(int ch);
int 	is_redirect(t_str *tstr);
void	print_charpp(char **s);
int		switch_quo(int ch, int *squo, int *dquo);

// const char* state_to_string(t_state state);
// int		expand_env(t_vec2 *v2, char **s); cfr. fvec2_deep_copy()

#endif // TMP_UTILS_H
