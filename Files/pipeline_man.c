#include "pipeline_man.h"
#include "builtin_v1.h"
#include "fvec2_man.h"
#include "tmp_utils.h"
#include "utility.h"
#include "command_v1.h"
#include <sys/wait.h>                     
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: remove the following
#include <stdio.h>
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void pipe_init_pipe(t_pi *pi)
{
	fprintf( tracciato, "pipe_init_pipe(t_pi*)\n" );
	// TODO: chiedere ad Ansi se questa aggiunta va bene:
	pi->fd_pipes[0] = 0;
	pi->fd_pipes[1] = 1;
	// ^^^^^^^^^^^^^^^^^^^^
	pi->args = NULL;
	pi->infile = NULL;
	pi->outfile = NULL;
	pi->here_doc = NULL;
	pi->append = 0;
	pi->cmd = NULL;
}

int pipe_add_path_to_cmd(t_pi *pi)
{
	fprintf( tracciato, "pipe_add_path_to_cmd(t_pi*)\n" );
	t_vec	path;
	int		i;
	char	*tmp;

	fvec_init(&path, 0);
	expand_path(&path);
	// TODO: remove the folllowing
	// printf( "\n=============\nTest on path\n");
	// fvec_print_vec(&path);
	// printf( "End test on path\n=============\n");
	// ^^^^^^^^^^^^^^^^
	i = 0;
	while (path.size > i)
	{
		tmp = my_strjoin(path.tstr[i].s, "/");
		pi->cmd = my_strjoin(tmp, pi->args[0]);
		free(tmp);
		// printf("%s\n", cmd);
		if (!access(pi->cmd, X_OK))
		{
			fvec_destroy(&path);
			return(1);
		}
		free(pi->cmd);
		++i;
	}
	fvec_destroy(&path);
	return (0);
}

void pipe_parse_redirect(t_pi *pi, t_vec *vec, int *i)
{
	fprintf( tracciato, "pipe_parse_redirect(t_pi*, t_vec*, %d)\n", *i );
	if (vec->tstr[*i].state == less)
		pi->infile = vec->tstr[++*i].s;
	// CASE >
	else if (vec->tstr[*i].state == great)
		pi->outfile = vec->tstr[++*i].s;
	// CASE >>
	else if (vec->tstr[*i].state == greatgreat)
	{
		pi->outfile = vec->tstr[++*i].s;
		pi->append = 1;
	}
	// CASE <<
	else if (vec->tstr[*i].state == lessless)
		pi->here_doc = vec->tstr[++*i].s;
}

/*
Funzione take_commands: Questa funzione prepara un array di argomenti da
passare a execute_command basandosi su un vettore di comandi (t_vec).
Filtra i comandi per redirezionamenti e parole, allocando dinamicamente spazio
per gli argomenti e copiandoli.
Alla fine, chiama execute_command con il primo argomento come nome del comando.
*/
/*
** pipe_tell_cmds_apart(): assumes first parameter contains a list of t_str
**                         settted like so:
**                         t_str[0] --> a command, like ls or cat or echo or...
**                         t_str[1...] --> the arguments of the commmmand
** The function make the passed t_pi->args pointer point to the command and its
** arguments, in order, so that it suit execve() requirements.
*/
void pipe_tell_cmds_apart(t_vec *cmd, char **envp, t_pi *pi)
{
	fprintf( tracciato, "pipe_tell_cmds_apart(t_vec*, char**, t_pi*)\n" );
	int i;
	int j;

	pi->args = malloc((size_t)(pipe_count_words_in_tvec(cmd)+1) * sizeof(char*));
	i = 0;
	j = 0;
	while (cmd->size > i)
	{
		if (is_redirect(&cmd->tstr[i]))
			pipe_parse_redirect(pi, cmd, &i);
		else if (cmd->tstr[i].state == word)
		{
			pi->args[j] = cmd->tstr[i].s;
			j++;
		}
		i++;
	}
	pi->args[j] = NULL;
	pipe_add_path_to_cmd(pi);
	pi->pid = fork();
	// FIXME: correct the following part: pipe_tell_cmds_apart(() should
	//        perform exactly one task. It should not call pipe_execute_cmd();
	if (pi->pid == 0)
		pipe_execute_cmd(pi, envp);
	else
	{
		waitpid(pi->pid, NULL, 0);
		close(pi->fd_pipes[1]);
	}
	free(pi->args);
}

void pipe_open_pipes(t_vec2 *vec2, char **envp)
{
	fprintf( tracciato, "pipe_open_pipes(t_vec*, char**, t_pi*)\n" );
	int 	i;
	int		fd[2];
	t_pi	pi;
	
	pipe_init_pipe(&pi);
	if (1 == vec2->size)
	{
		pipe_tell_cmds_apart(vec2->tvec, envp, &pi);
		return ;
	}
	i = 0;
	while (vec2->size > i)
	{
		if (i == 0)
		{	
			pipe(fd);
			pi.fd_pipes[0] = 0;
			pi.fd_pipes[1] = fd[1];
		}
		else if (i < vec2->size - 1)
		{
			pi.fd_pipes[0] = fd[0];
			pipe(fd);
			pi.fd_pipes[1] = fd[1];
		}
		else if (i == vec2->size - 1)
		{
			pi.fd_pipes[0] = fd[0];
			pi.fd_pipes[1] = 1;
		}
		pipe_tell_cmds_apart(&vec2->tvec[i], envp, &pi);
		i++;
	}
	fvec2_destroy(vec2);
}

int pipe_execute_cmd(t_pi *pi, char **envp)
{
	fprintf( tracciato, "pipe_execute_cmd(t_vec*, char**, t_pi*)\n" );
	int fd;

	if (built_is_builtin_cmd(*pi->args))	// spostare?
	{
		printf("Inizio builtin: %s\n", pi->args[0]);
		if(exec_builtins((char *)pi->args[0], pi->args, envp) == -1)
		{
			printf("oops\n");
			return(-1);
		}
	}
	printf("Fine builtin: %s\n", pi->args[0]);
	// si eliminare questa riga e vedere l'output reale( con execve) e quello
	// del nostro builtin!!!
	return (1);
	if (pi->fd_pipes[0] != 0)
	{
		dup2(pi->fd_pipes[0], STDIN_FILENO);
		close(pi->fd_pipes[0]);
	}
	if (pi->fd_pipes[1] != 1)
	{
		dup2(pi->fd_pipes[1], STDOUT_FILENO);
		close(pi->fd_pipes[1]);
	}
	if (pi->infile)
	{
		fd = open(pi->infile, R_OK);
		if (pi->fd_pipes[0] != 0)
			dup2(fd, pi->fd_pipes[0]);
		else
			dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (-1 == execve(pi->cmd, pi->args, envp))
		return(0);
	return(1);
}


int pipe_count_words_in_tvec(t_vec *v)
{
	fprintf( tracciato, "pipe_count_words_in_tvec(t_vec*)\n" );
	int i;
	int len;

	i = 0;
	len = 0;
	while (v->size > i)
	{
		if (is_redirect(&v->tstr[i]))
			++i;
		else if (v->tstr[i].state == word)
			++len;
		++i;
	}
	return (len);
}
