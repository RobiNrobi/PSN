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
CC      := cc -Wall -Werror -Wextra -g
RM      := rm -f

# =============================================================================
#                        Modified predefined variables
# =============================================================================
#ARFLAGS := crsv --> v: verbose
#ARFLAGS := crs

# NOTE: -g (debug) option required by Valgrind. Remove it on release:
CFLAGS  := -Wall -Wextra -Werror
ifdef deb
CFLAGS :=  $(CFLAGS) -g
endif

# NOTE: remove sanitize address on release or to test with valgrind:
ifdef sa
# LDFLAGS: Extra flags to give to compilers when they are supposed to invoke the
#          linker, ‘ld’, such as -L.
#          Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS :=  -fsanitize=address              \
			-fsanitize=alignment            \
			-fsanitize=float-cast-overflow  \
			-fsanitize=float-divide-by-zero \
			-fsanitize=null                 \
			-fsanitize=undefined
endif
LDFLAGS :=  $(LDFLAGS)

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

COMMON_DEPS := 

COMMON_SOURCES := 

BASE_DEPS := $(COMMON_DEPS)		\
				../_extra.h		\
				fstr_man.h		\
				fvec_man.h		\
				fvec2_man.h		\
				minshell.h		\
				parser_man.h	\
				token_man.h		\
				utility.h


BASE_SOURCES := $(COMMON_SOURCES)	\
					../_extra.c		\
					fstr_man.c		\
					fvec_man.c		\
					fvec2_man.c		\
					minishell.c		\
					parser_man.c	\
					token_man.c		\
					utility.c

BASE_OBJECTS := $(BASE_SOURCES:.c=.o)

BONUS_NAME := 

BONUS_DEPS := $(DEPS)

BONUS_SOURCES :=  $(COMMON_SOURCES)

BONUS_OBJECTS := $(BONUS_SOURCES:.c=.o)

# NOTE: 'exec' is to test with Valgrind. Remove it on release:
.PHONY: all bonus clean fclean re
ifdef val
.PHONY: exec
endif

all: $(NAME)

# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html
# The following rule does the right thing for a simple program with only one
# source file. It will also do the right thing if there are multiple object
# files (presumably coming from various other source files), one of which has a
# name matching that of the executable file.
# [...] when there is no object file whose name derives from the executable
# file name, you must write an explicit command for linking.
$(NAME): $(BASE_OBJECTS)
#		$(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)
#		$(CC) $(LDFLAGS) $(BASE_OBJECTS) -o $(NAME) $(LOADLIBES) $(LDLIBS)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJECTS)
#		$(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)
#		$(CC) $(LDFLAGS) $(BONUS_OBJECTS) -o $(BONUS_NAME) $(LOADLIBES) $(LDLIBS)

$(BASE_OBJECTS): $(BASE_SOURCES) $(DEPS)
#	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^

$(BONUS_OBJECTS): $(BONUS_SOURCES) $(BONUS_DEPS)
#	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^

clean: 
	$(RM) $(BASE_OBJECTS)
	$(RM) $(BONUS_OBJECTS)
	$(RM) *.gch
	$(RM) *.txt

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re: fclean all

exec:
ifdef val
	valgrind 							\
	--leak-check=full					\
	--log-file=AAAAA_VALGRIND_LOG.txt	\
	--read-inline-info=yes				\
	-s									\
	--show-leak-kinds=all				\
	--trace-children=yes				\
	--track-fds=yes						\
	--track-origins=yes					\
	-v									\
	--vgdb=full							\
	./$(NAME)
	printf "\n\n\t===== AAAAA_VALGRIND_LOG.txt ====\n"
	cat AAAAA_VALGRIND_LOG.txt
else
	./$(NAME)
#	printf "\n\n\t===== tracciato.txt ====\n"
#	cat tracciato.txt
endif
