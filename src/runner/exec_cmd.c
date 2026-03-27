/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:55:37 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/25 18:49:19 by achigvin         ###   ########.fr       */
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
	(void)env;
	if (!ft_strcmp(cmd_argv[0], "echo"))
		return (builtin_echo(cmd_argv));
	if (!ft_strcmp(cmd_argv[0], "cd"))
		return (builtin_cd(cmd_argv));
	if (!ft_strcmp(cmd_argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd_argv[0], "export"))
		return (builtin_export());
	if (!ft_strcmp(cmd_argv[0], "unset"))
		return (builtin_unset(cmd_argv, &env));
	if (!ft_strcmp(cmd_argv[0], "env"))
		return (builtin_env(env, cmd_argv));
	if (!ft_strcmp(cmd_argv[0], "exit"))
		return (builtin_exit(cmd_argv));
	return (EXIT_FAILURE);
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
		shell->exit_status = apply_redirs(cmd->redirs);
		if (shell->exit_status != 0)
			return (shell->exit_status);
		return (execute_builtin(cmd->argv, shell->env));
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
