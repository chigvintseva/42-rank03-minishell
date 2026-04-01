/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:29:29 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/01 18:40:13 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct	s_shell
{
	char			**env;
	int				exit_status;
	int				run_further;
	unsigned int	heredoc_id;
} t_shell;

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "runner.h"

int		case_error(char *msg, int code);
char	**clean_env(char **env);
void	exit_with_status(int status);
void	exit_with_error(char *arg);
void	free_env_copy(char **env_copy, size_t cnt);
int		init_shell(t_shell *shell, char **envp);
void	shell_loop(t_shell *shell);
int		minishell(char *input, t_shell *shell);
int		handel_heredocs(t_cmd *cmd, t_shell *shell);
void	free_shell(t_shell *shell);
int		only_space(char *str);

#endif