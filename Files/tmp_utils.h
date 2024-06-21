#ifndef TMP_UTILS_H
#define TMP_UTILS_H

#include "fvec_man.h"

t_vec	*expand_path(t_vec *v);
// const char* state_to_string(t_state state);
int		is_quote_or_pipe(int ch);
int		switch_quo(int ch, int *squo, int *dquo);
int 	is_redirect(t_str tstr);

#endif // TMP_UTILS_H
