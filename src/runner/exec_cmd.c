/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:55:37 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/08 19:36:40 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

static void	cmd_no_permission(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	exit(126);
}

static int	check_errno()
{
	if (errno == ENOENT)
		return (127);
	if (errno == EACCES || errno == EISDIR 
		|| errno == ENOEXEC || errno == ENOTDIR) 
		return (126);
	return (EXIT_FAILURE);
}

static void	exec_with_env(char *path, char **argv, char **env, int free_path)
{
	char	**exec_env;
	int		code;

	exec_env = clean_env(env);
	if (!exec_env)
	{
		if (free_path)
			free(path);
		exit_with_error("clean_env", EXIT_FAILURE);
	}
	execve(path, argv, exec_env);
	free_matrix(exec_env);
	if (free_path)
		free(path);
	code = check_errno();
	exit_with_error(argv[0], code);
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
			exit_with_error(cmd_argv[0], EXIT_FAILURE);
		if (!perm_error)
			cmd_not_found(cmd_argv[0]);
		cmd_no_permission(cmd_argv[0]);
	}
	exec_with_env(cmd_path, cmd_argv, env, 1);
}

static void	check_is_dir(char *cmd_path)
{
	struct stat	st;

	if (stat(cmd_path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_path, 2);
			ft_putendl_fd(": Is a directory", 2);
			exit(126);
		}
	}
}

static void	execute_external(char **cmd_argv, char **env)
{
	if (ft_strchr(cmd_argv[0], '/'))
	{
		check_is_dir(cmd_argv[0]);
		exec_with_env(cmd_argv[0], cmd_argv, env, 0);
	}
	resolve_and_exec(cmd_argv, env);
}

static int	restore_stdio(int backup[2])
{
	if (dup2(backup[0], 0) == -1 || dup2(backup[1], 1) == -1)
	{
		close(backup[0]);
		close(backup[1]);
		return (case_error("Dup2", EXIT_FAILURE));
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
		return (case_error("Dup", EXIT_FAILURE));
	backup[1] = dup(1);
	if (backup[1] == -1)
		return (close(backup[0]), case_error("Dup", EXIT_FAILURE));
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
