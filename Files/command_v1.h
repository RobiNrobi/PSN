#ifndef COMMAND_V1_H
#define COMMAND_V1_H

#include <fcntl.h>

int exec_cd(char *cmd, char **ag, char **env);
int exec_echo(char *cmd, char **argl);
int	exec_builtins(char *cmd, char **argl, char **envp);
int	exec_exit(char *cmd);
int	exec_pwd(char *cmd);

#endif // COMMAND_V1_H
