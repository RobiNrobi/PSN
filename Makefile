# ============================================================================
#                                   42 rules
# ============================================================================
# Your Makefile must at least contain the rules $(NAME), all, clean, fclean
# and re.
# Program name ________
# Turn in files __________
# Makefile NAME, all, clean, fclean, re
# Declaring global variables is forbidden.
# If you need helper functions to split a more complex function, define them as
# static functions. This way, their scope will be limited to the appropriate
# file.
# Place all your files at the root of your repository.
# Turning in unused files is forbidden.
# Every .c files must compile with the fl ags -Wall -Wextra -Werror.
# You must use the command ar to create your library. Using the libtool command
# is forbidden.
# Your libft.a has to be created at the root of your repository.
# =============================================================================
#                           Predefined variables
# =============================================================================
#AR      := ar
CC      := cc
RM      := rm -f

# =============================================================================
#                        Modified predefined variables
# =============================================================================
#ARFLAGS := crsv --> v: verbose
#ARFLAGS := crs

CFLAGS  := -O2                     \
           -g3                     \
           -Wall                   \
           -Wconversion            \
           -Werror                 \
           -Wextra                 \
           -Wfloat-equal           \
           -Wformat=2              \
           -Wmissing-prototypes    \
           -Wpedantic              \
           -Wshadow                \
           -Wno-unused-result      \
           -fno-omit-frame-pointer

# LDFLAGS: Extra flags to give to compilers when they are supposed to invoke the
#          linker, ‘ld’, such as -L.
#          Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS :=

RCFLAGS  := $(CFLAGS) -fsanitize=address    \
           -fsanitize=alignment             \
           -fsanitize=float-divide-by-zero  \
           -fsanitize=float-cast-overflow   \
           -fsanitize=null                  \
           -fsanitize=undefined

RLDFLAGS :=  $(LDFLAGS) -fsanitize=address  \
			-fsanitize=alignment            \
			-fsanitize=float-cast-overflow  \
			-fsanitize=float-divide-by-zero \
			-fsanitize=null                 \
			-fsanitize=undefined

# LDLIBS: Library flags or names given to compilers when they are supposed to
#         invoke the linker, ‘ld’.
#         LOADLIBES is a deprecated (but still supported) alternative to LDLIBS.
#         Non-library linker flags, such as -L, should go in the LDFLAGS
#         variable.
LDLIBS := -lreadline

# =============================================================================
#                              Built in rules
# =============================================================================
# Compiling C programs
# n.o is made automatically from n.c with a recipe of the form
# ‘$(CC) $(CPPFLAGS) $(CFLAGS) -c’.

# Linking a single object file
# n is made automatically from n.o by running the C compiler to link the
# program. The precise recipe used is
# ‘$(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)’. 


# =============================================================================
#                              This makefile
# =============================================================================
NAME := minishell

BASE_DEPS := 	_extra.h             \
				Files/builtin_v1.h   \
				Files/command_v1.h   \
				Files/fstr_man.h     \
				Files/fvec_man.h     \
				Files/fvec2_man.h    \
				Files/minshell.h     \
				Files/parser_man.h   \
				Files/pipeline_man.h \
				Files/tmp_utils      \
				Files/token_man.h    \
				Files/utility.h      \
				Files/env/env.h


BASE_SOURCES := 	_extra.c             \
					Files/builtin_v1.c   \
					Files/command_v1.c   \
					Files/fstr_man.c     \
					Files/fvec_man.c     \
					Files/fvec2_man.c    \
					Files/minishell.c    \
					Files/parser_man.c   \
					Files/pipeline_man.c \
					Files/tmp_utils.c    \
					Files/token_man.c    \
					Files/utility.c      \
					Filese/env/env.c


BASE_OBJECTS := _extra.o             \
				builtin_v1.o   \
				command_v1.o   \
				fstr_man.o     \
				fvec_man.o     \
				fvec2_man.o    \
				minishell.o    \
				parser_man.o   \
				pipeline_man.o \
				tmp_utils.o    \
				token_man.o    \
				utility.o      \
				env.o


BASE_ASAN_OBJECTS := _extra.o__      \
 					 builtin_v1.o_   \
 					 command_v1.o_   \
 					 fstr_man.o_     \
 					 fvec_man.o_     \
 					 fvec2_man.o_    \
 					 minishell.o_    \
 					 parser_man.o_   \
 					 pipeline_man.o_ \
 					 tmp_utils.o_    \
 					 token_man.o_    \
					 utility.o_      \
					 env.o_          \
					 env_utils.o_

NAME_ASAN := asan_minishell

.PHONY: all bonus clean fclean re exec

%.o_ : Files/%.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(RCFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(NAME_ASAN) $(BASE_OBJECTS)
		@$(CC) $(LDFLAGS) $(BASE_OBJECTS) -o $(NAME) $(LOADLIBES) $(LDLIBS)
		@$(RM) $(BASE_OBJECTS)
		@echo executing $(NAME):
		@valgrind --leak-check=full --log-file=_VALGRIND_LOG.txt --show-leak-kinds=all ./$(NAME)
		@echo
		@echo ----------------------------------------------------------------
		@echo valgrind log:
		@cat _VALGRIND_LOG.txt
		@echo

$(NAME_ASAN): $(BASE_ASAN_OBJECTS)
		@$(CC) $(LDFLAGS) $(RLDFLAGS) $(BASE_ASAN_OBJECTS) -o $(NAME_ASAN) $(LOADLIBES) $(LDLIBS)
		@$(RM) $(BASE_ASAN_OBJECTS)
		@$(RM) $(NAME_ASAN)

_extra.o__ : _extra.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(RCFLAGS) -c _extra.c -o _extra.o__

$(BASE_OBJECTS): $(BASE_SOURCES) $(DEPS)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $^

clean: 
	@$(RM) $(BASE_OBJECTS)
	@$(RM) *.gch

fclean: clean
	@$(RM) $(NAME)
	@$(RM) tracciato.txt
	@$(RM) _VALGRIND_LOG.txt

re: fclean all

exec:
	valgrind 							\
	--leak-check=full					\
	--log-file=AAAAA_VALGRIND_LOG.txt	\
	--show-leak-kinds=all				\
	--vgdb=full							\
	./$(NAME)
