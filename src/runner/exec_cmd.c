/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:55:37 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/29 23:22:15 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_external(char **cmd_argv, char **env)
{
	char	*cmd_path;
	int		perm_error;

	errno = 0;
	if (!ft_strchr(cmd_argv[0], '/'))
	{
		perm_error = 0;
		cmd_path = parsing(cmd_argv[0], env, &perm_error);
		if (!cmd_path)
		{
			if (errno)
				exit_with_error();
			else if (!perm_error)
			{
				ft_putstr_fd(cmd_argv[0], 2);
				ft_putendl_fd(": command not found", 2);
				exit(127);
			}
			else
			{
				ft_putstr_fd("minishell: Permission denied: ", 2);
				ft_putendl_fd(cmd_argv[0], 2);
				exit(126);
			}
		}
		if (execve(cmd_path, cmd_argv, clean_env(env)) == -1)
		{
			free(cmd_path);
			exit_with_error();
		}
	}
	else
	{
		if (execve(cmd_argv[0], cmd_argv, clean_env(env) == -1)
			exit_with_error();
	}
}

static int	run_redirs(t_redir *redirs)
{
	int	status;
	int	backup[2];

	backup[0] = dup(0);
	if (backup[0] == -1)
		return (case_error("Dup", 1));
	backup[1] = dup(1);
	if (backup[1] == -1)
	{
		close(backup[0]);
		return (case_error("Dup", 1));
	}
	status = apply_redirs(redirs);
	if (dup2(backup[0], 0) == -1 || dup2(backup[1], 1) == -1)
	{
		close(backup[0]);
		close(backup[1]);
		return (case_error("Dup2", 1));
	}
	close(backup[0]);
	close(backup[1]);
	return (status);
}

int	run_cmd(t_cmd *cmd, t_shell	*shell)
{
	pid_t	pid;
	int		status;

	if (!cmd)
		return (1);
	if (!cmd->argv)
		return (run_redirs(cmd->redirs)); //
	if (is_builtin(cmd->argv[0]))
		return (run_builtin(cmd, shell));
	pid = fork();
	if (pid == -1)
		return (case_error("Fork", 1));
	if (pid == 0)
	{
		shell->exit_status = apply_redirs(cmd->redirs);
		if (shell->exit_status != 0)
			exit(shell->exit_status);
		execute_external(cmd->argv, shell->env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (shell->exit_status = WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (shell->exit_status = 128 + WTERMSIG(status));
	return (-1);
}
