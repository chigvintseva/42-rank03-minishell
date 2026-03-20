/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:19:26 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/20 22:24:17 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include "minishell.h"
# include <sys/wait.h>
# include <fcntl.h>

typedef struct	s_fds
{
	int	infd;
	int	outfd;
	int	pipefd[2];
}	t_fds;

int	run_cmd_node(t_ast *node, t_shell *shell);
int	run_pipe_node(t_ast *root, t_shell *shell);
int	runner(t_ast *node, t_shell *shell);
int	run_pipe(t_ast *root, t_shell *shell);

int		ft_strcmp(char *s1, char *s2);
void	free_matrix(char **matrix);
char	*free_return(char **to_free, char *to_return);

int		run_cmd(t_cmd *cmd, t_shell	*shell);
char	*parsing(char *cmd, char **envp, int *perm_error);
int		apply_redirs(t_redir *redirs);

int		builtin_echo();
int		builtin_cd();
int		builtin_pwd();
int		builtin_export();
int		builtin_unset();
int		builtin_env();
int		builtin_exit();

#endif