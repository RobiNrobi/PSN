#ifndef COMMAND_V1_H
#define COMMAND_V1_H

#include "fvec_man.h"

int		execute_command(char const *name, char *const argl[], char *const envp[]);
void	take_commands(t_vec *cmd, char **envp);
char	*my_strdup(const char *str);
void	*my_memcpy(void *dest, const void *src, int n);

#endif // COMMAND_V1_H
