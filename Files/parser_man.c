#include "parser_man.h"
#include "fvec_man.h"
#include "utility.h"
#include "token_man.h"
#include "../_extra.h"
// #include <readline/readline.h>
// #include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

//TODO: remove the following
extern FILE* tracciato;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int	pars_get_words_seq(t_vec *vec, char *line, char *envp[])
{
	fprintf( tracciato, "pars_get_words_seq(t_vec*, %s)\n", line );
	t_str str;

	if (!fvec_init(vec, 0, envp))
		return (0);
	if (!fstr_init(&str, 0))
	{
		fvec_destroy(vec);
		return (0);
	}
	pars_03(line, vec, str);
	return (1);
}

int pars_parsline(char *line, char *envp[])
{
	fprintf( tracciato, "parsline()\n" );
	t_vec	seq;

	//TODO: restore readline and delete the following lines:
	line = read_a_line("Viva Ansi!> ");
	// NOTE: the usage of readline() has been postponed because it causes memory
	//       leaks.
	// line = readline("Viva Ansi!> ");
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	//TODO: restore add_history:
	//	add_history(line);
	if (!line)
		return (0);
	if (error_quotes(line))
	{
		free(line);
		printf("Error: Unclosed Quotes!\n");
		return (0);
	}
	pars_get_words_seq(&seq, line, envp);
	fvec_print_vec(&seq);
	fvec_destroy(&seq);
	fclose(tracciato);
	exit(EXIT_FAILURE);
	return (1);
}

void pars_03(char *line, t_vec *vec, t_str str)
{
	fprintf( tracciato, "pars_03(%s, t_vec2*)\n", line );
	int		i;

	i = 0;
	while (line[i] && my_isspace(line[i]))
		++i;
	while (line[i])
	{
		if ('"' == line[i] || '\'' == line[i])
			quotes_man(line, &i, &str);
		else if (my_isalnum(line[i]))
			word_man(line, &i, &str);
		else if (my_isspace(line[i]))
			space_man(&str, vec);
		else if ('<' == line[i])
			less_man(line, &i, &str, vec);
		else if ('>' == line[i])
			great_man(line, &i, &str, vec);
		else if ('|' == line[i])
			pipe_man(line, &i, &str, vec);
		else if ('$' == line[i])
			dollar_man(line, &i, &str);
	++i;
	}
	if (str.state == word)
		close_laststr(&str, vec);
	free(line);
	fstr_destroy(&str);
}

void	close_laststr(t_str *str, t_vec *vec)
{
	fstr_add_char(str, '\0');
	fvec_add_str(vec, str);
	fstr_reset(str);
}
