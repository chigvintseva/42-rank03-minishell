/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:29:29 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 18:59:53 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"

typedef struct	s_shell
{
	char	**env;
	int		exit_status;
	int		run_further;
} t_shell;

int		init_shell(t_shell *shell, char **envp);
void	set_signals(void);
void	signal_handler(int signal);
void	shell_loop(t_shell *shell);
int		minishell(t_shell *shell, char *input);
void	free_shell(t_shell *shell);
int		case_error(char *msg, int code);
int		only_space(char *str);

#endif