#include "_extra.h"
#include "Files/fstr_man.h"		// my_getline() --> t_str
#include "Files/fvec2_man.h"
#include "Files/tmp_utils.h"
#include <stdio.h>
#include <stdlib.h>				// read_a_line() --> malloc
#include <unistd.h>				// my_getline() --> read()


FILE* tracciato = NULL;


void closef( void )
{
	if (tracciato) {
		fclose( tracciato );
		tracciato = NULL;
	}
}

char *my_getline( void )
{
	fprintf( tracciato, "my_getline()\n" );
	t_str str;
	fstr_init( &str, 0 );
	while (1)
	{
		int ch = getchar();
		if (feof(stdin))
			break;
		if (ferror(stdin))
		{
			perror( "getchar()" );
			printf( "getchar() error in function my_getline()\n" );
			break;
		} else {
			if ('\n' == ch)
				break;
			fstr_add_char( &str, (char)ch );
		}
	}
	fstr_close_str( &str );
	return str.s;
}

int openf(const char * const fname)
{
	tracciato = fopen( fname, "w+" );
	if (!tracciato)
		return (0);
	return (1);
}

char *read_a_line(const char * const str)
{
	fprintf( tracciato, "read_a_line(%s)\n", str );
	printf( "%s", str );

	// TODO: CHOOSE AN OPTION:
	// // OPTION 1
	// char* s = malloc( sizeof(char) * 256 );
	// int ret = scanf( "%s", s);
	// if (EOF == ret) {
	// 	printf( "BEWARE! EOF met\n" );
	// } else {
	// 	printf( "zero characters have been written\n" );
	// }
	// return s;

	// OPTION 2
	char* s = my_getline();
	return s;
}

void tests_minishell(char** env)
{
	//DEBUG:
	printf( "\n===============\nTest di debug su envp:\n" );
	t_vec2 tenv;
	fvec2_init( &tenv, 0 );
	printf( "\nDeep copying 'env' into a t_vec2...\n" );
	fvec2_deep_copy( &tenv, (char const *const *const)env );
	fvec2_print_vec2( &tenv );
	printf( "Converting back into char** and printing again:\n" );
	char** capra = fvec2_turn_into_charpp( &tenv, &capra );
	print_charpp( capra );
	// Freing memory:
	for (int i = 0; capra[i]; ++i) {
		free( capra[i] );
	}
	free( capra );
	fvec2_destroy( &tenv );
	printf( "End test su envp:\n===============\n" );
}
