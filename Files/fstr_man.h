#ifndef FSTR_MAN_H
#define FSTR_MAN_H


#ifndef DEFAULT_STR_SIZE
# define DEFAULT_STR_SIZE 15
#endif

typedef struct s_fstr
{
	int		size;
	int		capacity;
	char	*s;
}	t_str;

void	fstr_add_char(t_str *str, char c);
void	fstr_close_str(t_str *str);
int		fstr_copy(t_str *dest, t_str const *const orig);
int		fstr_copy_to_new(t_str *dest, t_str const *const orig);
void	fstr_destroy(t_str *str);
void	fstr_double_cap(t_str *str);
char	*fstr_init(t_str *str, int cap);
void	fstr_init_els(t_str *str);
void	fstr_print_str(t_str *str);
int		fstr_replace_from_pos(t_str *str, int ind, const char * const s);
int		fstr_reset(t_str *str);

// TODO: delete the following:
// Temporary / debug functions
void	fstr_print_str_n(t_str *str);

#endif // FSTR_MAN_H
