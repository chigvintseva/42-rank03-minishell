/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:55:37 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/25 19:21:32 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_builtin(char *cmd)
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

static int	execute_builtin(char **cmd_argv, char **env)
{
	if (!ft_strcmp(cmd_argv[0], "echo"))
		return (builtin_echo(cmd_argv));
	if (!ft_strcmp(cmd_argv[0], "cd"))
		return (builtin_cd());
	if (!ft_strcmp(cmd_argv[0], "pwd"))
		return (builtin_pwd(cmd_argv, env));
	if (!ft_strcmp(cmd_argv[0], "export"))
		return (builtin_export());
	if (!ft_strcmp(cmd_argv[0], "unset"))
		return (builtin_unset(cmd_argv, &env));
	if (!ft_strcmp(cmd_argv[0], "env"))
		return (builtin_env());
	if (!ft_strcmp(cmd_argv[0], "exit"))
		return (builtin_exit(cmd_argv));
	return (1);
}

static int	run_builtin(t_cmd *cmd, t_shell *shell)
{
	int	backup[2];
	int	result;

	backup[0] = dup(STDIN_FILENO);
	if (backup[0] == -1)
		return (case_error("Dup", 1));
	backup[1] = dup(STDOUT_FILENO);
	if (backup[1] == -1)
	{
		close(backup[0]);
		return (case_error("Dup", 1));
	}
	result = apply_redirs(cmd->redirs);
	if (result == 0)
		result = execute_builtin(cmd->argv, shell->env);
	if (dup2(backup[0], STDIN_FILENO) == -1
		|| dup2(backup[1], STDOUT_FILENO) == -1)
	{
		close(backup[0]);
		close(backup[1]);
		return (case_error("Dup2", 1));
	}
	close(backup[0]);
	close(backup[1]);
	return (result);
}

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
		if (execve(cmd_path, cmd_argv, env) == -1)
		{
			free(cmd_path);
			exit_with_error();
		}
	}
	else
	{
		if (execve(cmd_argv[0], cmd_argv, env) == -1)
			exit_with_error();
	}
}

int	run_cmd(t_cmd *cmd, t_shell	*shell)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->argv )
		return (1);
	if (is_builtin(cmd->argv[0]))
	{
		if (!cmd->redirs)
			shell->exit_status = execute_builtin(cmd->argv, shell->env);
		else
			shell->exit_status = run_builtin(cmd, shell);
		return (shell->exit_status);
	}
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
