/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:55:37 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/20 22:55:58 by achigvin         ###   ########.fr       */
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

static int	execute_builtin(char **cmd_arg)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		return (builtin_echo());
	if (!ft_strcmp(cmd_arg[0], "cd"))
		return (builtin_cd());
	if (!ft_strcmp(cmd_arg[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd_arg[0], "export"))
		return (builtin_export());
	if (!ft_strcmp(cmd_arg[0], "unset"))
		return (builtin_unset());
	if (!ft_strcmp(cmd_arg[0], "env"))
		return (builtin_env());
	if (!ft_strcmp(cmd_arg[0], "exit"))
		return (builtin_exit());
	return (1);
}

static void	execute_external(t_cmd *cmd, char **env)
{
	char	*cmd_path;
	int		perm_error;

	perm_error = 0;
	if (!ft_strchr(cmd->argv[0], '/'))
	{
		cmd_path = parsing(cmd->argv[0], env, &perm_error);
		if (!cmd_path)
		{
			if (!perm_error)
			{
				ft_putstr_fd("minishell: command not found: ", 2);
				ft_putendl_fd(cmd->argv[0], 2);
				exit(127);
			}
			else
			{
				ft_putstr_fd("minishell: Permission denied: ", 2);
				ft_putendl_fd(cmd->argv[0], 2);
				exit(126);
			}
		}
		if (execve(cmd_path, cmd->argv, env) == -1)
		{
			free(cmd_path);
			exit_with_error("execve", 126); // Check errno: EACCES/EISDIR → 126; ENOENT/ENOTDIR → 127
		}
	}
	else
	{
		if (execve(cmd->argv[0], cmd->argv, env) == -1)
			exit_with_error("execve", EXIT_FAILURE); // Check errno: EACCES/EISDIR → 126; ENOENT/ENOTDIR → 127
	}
}

int	run_cmd(t_cmd *cmd, t_shell	*shell)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->argv)
		return (1);
	shell->exit_status = apply_redirs(cmd->redirs);
	if (shell->exit_status != 0)
		return (shell->exit_status);
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(cmd->argv));
	pid = fork();
	if (pid == -1)
		return (case_error("Fork", 1));
	if (pid == 0)
		execute_external(cmd, shell->env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
            shell->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
            shell->exit_status = 128 + WTERMSIG(status);
	return (0);
}
