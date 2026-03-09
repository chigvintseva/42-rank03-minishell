#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
#include <errno.h>
#include <string.h>
# include "libft_printf/libft.h"
# include "lexing.h"

void	exit_with_error(char *msg, int code);

#endif