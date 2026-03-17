/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:29:29 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 19:35:24 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h> //cc main.c -lreadline
# include <signal.h>
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"

typedef struct	s_shell
{
	char	**env;
	int		exit_status;
	int		run_further;
} t_shell;

int		case_error(char *msg);
int		init_shell(t_shell *shell, char **envp);
void	shell_loop(t_shell *shell);
int		minishell(char *input, t_shell *shell);
void	free_shell(t_shell *shell);
int		only_space(char *str);
// temp:
int	runner(t_ast *root, t_shell *shell);

#endif