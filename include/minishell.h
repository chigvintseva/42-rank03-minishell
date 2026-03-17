/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:29:29 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 15:13:48 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"

// keys thatrequire rection and no reaction for the last one
# define CTRL_C
# define CTRL_D
# define CTRL_BACKSLASH

typedef struct	s_shell
{
	char	**env;
	int		exit_status;
	int		run_further;
} t_shell;

void	exit_with_error(char *msg, int code);

#endif