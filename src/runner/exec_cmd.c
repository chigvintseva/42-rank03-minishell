/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:55:37 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/10 16:19:44 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	run_redirs(t_redir *redirs)
{
	int	status;
	int	backup[2];

	backup[0] = dup(0);
	if (backup[0] == -1)
		return (case_error("Dup", EXIT_FAILURE));
	backup[1] = dup(1);
	if (backup[1] == -1)
		return (close(backup[0]), case_error("Dup", EXIT_FAILURE));
	status = apply_redirs(redirs);
	if (dup2(backup[0], 0) == -1 || dup2(backup[1], 1) == -1)
	{
		close(backup[0]);
		close(backup[1]);
		return (case_error("Dup2", EXIT_FAILURE));
	}
	close(backup[0]);
	close(backup[1]);
	return (status);
}

static void	child_cmd(t_cmd *cmd, t_shell *shell)
{
	shell->exit_status = apply_redirs(cmd->redirs);
	if (shell->exit_status != 0)
		exit(shell->exit_status);
	execute_external(cmd->argv, shell->env);
}

static int	parent(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (shell->exit_status = WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (shell->exit_status = 128 + WTERMSIG(status));
	return (-1);
}

int	run_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	if (!cmd)
		return (EXIT_FAILURE);
	if (!cmd->argv)
		return (run_redirs(cmd->redirs));
	if (is_builtin(cmd->argv[0]))
		return (run_builtin(cmd, shell));
	pid = fork();
	if (pid == -1)
		return (case_error("Fork", 1));
	if (pid == 0)
		child_cmd(cmd, shell);
	return (parent(pid, shell));
}
