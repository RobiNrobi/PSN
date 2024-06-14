#ifndef FSTR_MAN_H
#define FSTR_MAN_H


#ifndef DEFAULT_STR_SIZE
# define DEFAULT_STR_SIZE 15
#endif

typedef enum state
{
	dq,
	sq,
	less,
	lessless,
	great,
	greatgreat,
	pipes,
	word,
	dollar,
	other,
}	t_state;

typedef struct s_fstr
{
	int		size;
	int		capacity;
	char	*s;
	t_state state;
}	t_str;

void	fstr_add_char(t_str *str, char c);
int		fstr_copy(t_str *dest, t_str const *const orig);
int		fstr_copy_to_new(t_str *dest, t_str const *const orig);
void	fstr_destroy(t_str *str);
void	fstr_double_cap(t_str *str);
char	*fstr_init(t_str *str, int cap);
void	fstr_init_els(t_str *str);
void	fstr_print_str(t_str *str);
int		fstr_reset(t_str *str);

#endif // FSTR_MAN_H
