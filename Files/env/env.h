#ifndef ENV_H
#define ENV_H
#include "../fvec_man.h"

typedef struct s_env_elem
{
	char				*key;
	char				*value;
	int					size;
	char				*line;
	struct s_env_elem	*next;
	struct s_env_elem	*prev;
}	t_elem;

typedef struct s_env
{
	t_elem				*head;
	char				**env;
	int					size;
}	t_env;

int			is_builtin_cmd(char const *const s);
t_env		*init_env(t_env *env);
t_elem		*lst_new(char *line);
void		lst_env_add_back(t_env *env, t_elem *new);
t_env		*start_env(char **tab);
int			ft_strchr(char *s, int c);
int			ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, int len);
char		*ft_strdup(const char *s);
char		**convert_array(t_env *env);
void		print_env_arr(char **env);
void		print_env(t_env *env);
void		del_env_elem(t_env *env, t_elem *elem);
void		del_env(t_env *env);



#endif // ENV_H
