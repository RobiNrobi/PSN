#include "env.h"
#include "../utility.h"

// TODO: remove the following
#include <stdio.h>
extern FILE *tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

t_env	*init_env(t_env *env)
{
	env = my_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	return (env);
}

t_elem	*lst_new(char *line)
{
	t_elem	*elem;
	char		*key;
	char		*value;
	int			i;

	i = ft_strchr(line, '=');
	elem = my_calloc(sizeof(t_elem), 1);
	if (i != -1)
	{
		key = ft_substr(line, 0, i);
		value = ft_substr(line, (unsigned)(i + 1), ft_strlen(line) - i);
		if (!key || !value || !elem)
		// BUG: clang: potential leak of memory
			return (NULL);
		elem->key = key;
		elem->value = value;
		elem->line = ft_strdup(line);
	}
	else
	{
		elem->key = ft_strdup(line);
		elem->value = NULL;
	}
	elem->size = ft_strlen(line);
	return (elem);
}

void	lst_env_add_back(t_env *env, t_elem *new)
{
	t_elem	*tmp;

	tmp = env->head;
	if (!env->head)
		env->head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	env->size++;
}

t_env	*start_env(char **tab)
{
	t_env	*env;
	int		i;	

	env = NULL;
	env = init_env(env);
	env->env = tab;
	i = 0;
	while (tab[i])
		lst_env_add_back(env, lst_new(tab[i++]));
	return (env);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strlen(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0' && s)
	{
		a++;
	}
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*subs;
	int	i;
	int	j;

	if (!s)
		return (NULL);
	if ((int)start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	subs = (char *)malloc((size_t)(len + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >=(int) start && j < len)
			subs[j++] = s[i];
		i++;
	}
	subs[j] = '\0';
	return (subs);
}

char	*ft_strdup(const char *s)
{
	char		*sdup;
	const char	*a;
	size_t		i;

	i = 0;
	a = s;
	while (*s)
	{
		i++;
		s++;
	}
	sdup = (char *)malloc((1 + i) * sizeof(const char));
	if (!sdup)
		return (NULL);
	s = (char *)sdup;
	while (*a)
	{
		*sdup = *a;
		a++;
		sdup++;
	}
	*sdup = '\0';
	return ((char *)s);
}

