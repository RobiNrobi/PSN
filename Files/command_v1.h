#ifndef COMMAND_V1_H
#define COMMAND_V1_H
#define EQUAL 0
#include "fvec_man.h"
#include "env/env.h"


int		execute_command(const char *name, char **argl, char **envp, t_env *env);
void	take_commands(t_vec *cmd, char **envp, t_env *env);
char	*my_strdup(const char *str);
void	*my_memcpy(void *dest, const void *src, int n);
int		exec_pwd(char *cmd);
int		exec_builtins(char *cmd, char **argl,char **envp);
int		check_builtins(char *cmd);
int		exec_exit(char *cmd);



#endif // COMMAND_V1_H
