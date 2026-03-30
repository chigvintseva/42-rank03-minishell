/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:55:37 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/30 17:54:49 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	clean_env_len(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			len++;
		i++;
	}
	return (len);
}

static char	**clean_env(char **env)
{
	char	**clean;
	int		i;
	int		j;

	clean = malloc(sizeof(char *) * (clean_env_len(env) + 1));
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			clean[j] = ft_strdup(env[i]);
			if (!clean[j])
				return (free_matrix(clean), NULL);
			j++;
		}
		i++;
	}
	clean[j] = NULL;
	return (clean);
}

static void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

static void	cmd_no_permission(char *cmd)
{
	ft_putstr_fd("minishell: Permission denied: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(126);
}

static void	exec_with_env(char *path, char **argv, char **env, int free_path)
{
	char	**exec_env;

	exec_env = clean_env(env);
	if (!exec_env)
	{
		if (free_path)
			free(path);
		exit(EXIT_FAILURE);
	}
	execve(path, argv, exec_env);
	free_matrix(exec_env);
	if (free_path)
		free(path);
	exit_with_error();
}

static void	resolve_and_exec(char **cmd_argv, char **env)
{
	char	*cmd_path;
	int		perm_error;

	perm_error = 0;
	errno = 0;
	cmd_path = parsing(cmd_argv[0], env, &perm_error);
	if (!cmd_path)
	{
		if (errno)
			exit_with_error();
		if (!perm_error)
			cmd_not_found(cmd_argv[0]);
		cmd_no_permission(cmd_argv[0]);
	}
	exec_with_env(cmd_path, cmd_argv, env, 1);
}

static void	execute_external(char **cmd_argv, char **env)
{
	if (ft_strchr(cmd_argv[0], '/'))
		exec_with_env(cmd_argv[0], cmd_argv, env, 0);
	resolve_and_exec(cmd_argv, env);
}

static int	restore_stdio(int backup[2])
{
	if (dup2(backup[0], 0) == -1 || dup2(backup[1], 1) == -1)
	{
		close(backup[0]);
		close(backup[1]);
		return (case_error("Dup2", 1));
	}
	close(backup[0]);
	close(backup[1]);
	return (EXIT_SUCCESS);
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
		return (close(backup[0]), case_error("Dup", 1));
	status = apply_redirs(redirs);
	if (restore_stdio(backup) != 0)
		return (EXIT_FAILURE);
	return (status);
}

static void	child_cmd(t_cmd *cmd, t_shell *shell)
{
	shell->exit_status = apply_redirs(cmd->redirs);
	if (shell->exit_status != 0)
		exit(shell->exit_status);
	execute_external(cmd->argv, shell->env);
}

static int	wait_cmd(pid_t pid, t_shell *shell)
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
	return (wait_cmd(pid, shell));
}
