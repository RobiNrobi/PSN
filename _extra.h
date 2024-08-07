#ifndef _EXTRA_H
#define _EXTRA_H

void closef(void);
char* my_getline(void);
int openf(char const *const fname);
char* read_a_line(char const *const str);

void tests_minishell(char** two);

#endif // _EXTRA_H
// NOTE: Admitted functions:
// access
// add_history
// chdir
// close
// closedir
// dup
// dup2
// execve
// exit
// fork
// free
// fstat
// getcwd
// getenv
// ioctl
// isatty
// kill
// lstat
// malloc
// open
// opendir
// perror
// pipe
// printf
// read
// readdir
// readline
// rl_clear_history
// rl_on_new_line
// rl_redisplay
// rl_replace_line
// sigaction
// sigaddset
// sigemptyset
// signal
// stat
// strerror
// tcgetattr
// tcsetattr
// tgetent
// tgetflag
// tgetnum
// tgetstr
// tgoto
// tputs
// ttyname
// ttyslot
// unlink
// wait
// wait3
// wait4
// waitpid
// write
