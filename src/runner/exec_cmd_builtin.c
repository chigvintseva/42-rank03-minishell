/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:57:15 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 00:06:33 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(char **cmd_argv, t_shell *shell)
{
	if (!ft_strcmp(cmd_argv[0], "echo"))
		return (builtin_echo(cmd_argv));
	if (!ft_strcmp(cmd_argv[0], "cd"))
		return (builtin_cd(cmd_argv, shell->env));
	if (!ft_strcmp(cmd_argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd_argv[0], "export"))
		return (builtin_export(cmd_argv, shell));
	if (!ft_strcmp(cmd_argv[0], "unset"))
		return (builtin_unset(cmd_argv, &(shell->env)));
	if (!ft_strcmp(cmd_argv[0], "env"))
		return (builtin_env(shell->env, cmd_argv));
	if (!ft_strcmp(cmd_argv[0], "exit"))
		return (builtin_exit(cmd_argv, shell));
	return (EXIT_FAILURE);
}

int	run_builtin(t_cmd *cmd, t_shell *shell)
{
	int	backup[2];
	int	status;

	backup[0] = dup(0);
	if (backup[0] == -1)
		return (case_error("Dup", 1));
	backup[1] = dup(1);
	if (backup[1] == -1)
	{
		close(backup[0]);
		return (case_error("Dup", 1));
	}
	status = apply_redirs(cmd->redirs);
	if (status == 0)
		status = execute_builtin(cmd->argv, shell);
	if (dup2(backup[0], 0) == -1)
	{
		close(backup[0]);
		close(backup[1]);
		return (case_error("Dup2", 1));
	}
	if (dup2(backup[1], 1) == -1)
	{
		close(backup[0]);
		close(backup[1]);
		return (case_error("Dup2", 1));
	}
	close(backup[0]);
	close(backup[1]);
	return (status);
}
