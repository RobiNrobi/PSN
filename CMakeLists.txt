# cmake_minimum_required:
# Sets the minimum required version of cmake for a project.
# Also updates the policy settings [...].
cmake_minimum_required(VERSION 3.5)


# project:
# Sets the name of the project, and stores it in the variable PROJECT_NAME.
# When called from the top-level CMakeLists.txt also stores the project name in
# the variable CMAKE_PROJECT_NAME.
project(MiniShell_01 LANGUAGES C)


# add_executable:
# Add an executable target called <name> to be built from the source files
# listed in the command invocation.
add_executable(MiniShell_01
	_extra.h               _extra.c
	Files/builtin_v1.h     Files/builtin_v1.c
	Files/command_v1.h     Files/command_v1.c
	                       Files/execute_bunch.c
	Files/fstr_man.h       Files/fstr_man.c
	Files/fvec_man.h       Files/fvec_man.c
	Files/fvec2_man.h	   Files/fvec2_man.c
	Files/minishell.h      Files/minishell.c
	Files/parser_man.h     Files/parser_man.c
	Files/pipeline_man.h   Files/pipeline_man.c
	Files/tmp_utils.h      Files/tmp_utils.c
	Files/token_man.h      Files/token_man.c
	Files/utility.h        Files/utility.c
	Files/env/env.h        Files/env/env.c
	                       Files/env/env_utils.c
)


# target_include_directories:
# Specifies include directories to use when compiling a given target.
#target_include_directories(MiniShell_01 PRIVATE
#	${CMAKE_CURRENT_SOURCE_DIR}/Files/minilibx-linux/
#	/usr/include
#)


# target_compile_options:
# Adds options to the COMPILE_OPTIONS or INTERFACE_COMPILE_OPTIONS target
# properties.
# These options are used when compiling the given <target>, which must have
# been created by a command such as add_executable() or add_library() and must
# not be an ALIAS target.
# Note:
# These options are not used when linking the target.
# See the target_link_options() command for that.
# =============================================================================
#   Many usefull flags according with the compiler
# =============================================================================
if (${CMAKE_C_COMPILER_ID} STREQUAL GNU)
	message("Sanitize address DISABLED")
	target_compile_options(MiniShell_01 PRIVATE $<$<COMPILE_LANGUAGE:C>:
		-O2
		-g3
		-Wall
		-Wconversion
		-Werror
		-Wextra
		-Wfloat-equal
		-Wformat=2
		-Wmissing-prototypes
		-Wpedantic
		-Wshadow
		-Wno-unused-result
		-fno-omit-frame-pointer
		-Walloc-zero
		-Wduplicated-branches
		-Wduplicated-cond
		-Wlogical-op
		>)
	# -std=c17

elseif (${CMAKE_C_COMPILER_ID} STREQUAL Clang)
	message("Sanitize address ENABLED")
	target_compile_options(MiniShell_01 PRIVATE $<$<COMPILE_LANGUAGE:C>:
		-O2
		-g3
		-Wall
		-Wconversion
		-Werror
		-Wextra
		-Wfloat-equal
		-Wformat=2
		-Wmissing-prototypes
		-Wpedantic
		-Wshadow
		-Wno-unused-result
		-fno-omit-frame-pointer
		-fsanitize=address
		-fsanitize=alignment
		-fsanitize=float-divide-by-zero
		-fsanitize=float-cast-overflow
		-fsanitize=null
		-fsanitize=undefined
		>)
# -std=c17

    target_link_options(MiniShell_01 PRIVATE
		-fsanitize=address
		-fsanitize=alignment
		-fsanitize=float-cast-overflow
		-fsanitize=float-divide-by-zero
		-fsanitize=null
		-fsanitize=undefined
	)
endif()
# -----------------------------------------------------------------------------


# target_link_directories:
# Specifies the paths in which the linker should search for libraries when
# linking a given target.
# Each item can be an absolute or relative path, with the latter being
# interpreted as relative to the current source directory.
# These items will be added to the link command.
# (Correspondant: -L in GNU compilers and LDFLAGS in makefiles.)
# target_link_directories(MiniShell_01 PRIVATE
# 	${CMAKE_CURRENT_SOURCE_DIR}/Files/minilibx-linux/
# )


# target_link_libraries:
# Specify libraries or flags to use when linking a given target and/or its
# dependents.
# (Correspondant: -l in GNU compilers and LDLIBS in makefiles.)
# target_link_libraries(MiniShell_01 readline)



# include:
# Loads and runs CMake code from the file given.
include(GNUInstallDirs)


#install
# This command generates installation rules for a project.
# Install rules specified by calls to the install() command within a source
# directory are executed in order during installation.
install(TARGETS MiniShell_01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
