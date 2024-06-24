#ifndef COMMAND_V1_H
#define COMMAND_V1_H

#include "fvec_man.h"
#include "env/env.h"

#define EQUAL 0

struct s_pipe_info;
typedef struct s_pipe_info t_pi;

int		comm_execute_cmd(char const *name, char *argl[], char *envp[], /*da eliminare*/ t_env *env);

void	comm_take_cmds(t_vec *cmd, char **envp, /*da eliminare*/ t_env *env);
int		exec_pwd(char *cmd);
int		exec_builtins(char *cmd, char **argl,char **envp);
int		check_builtins(char *cmd);
int		exec_exit(char *cmd);

void	comm_parse_cmd(t_pi *pi);

//
int exec_cd(char *cmd, char **ag, char **env);



#endif // COMMAND_V1_H
