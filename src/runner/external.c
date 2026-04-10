/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:57:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/10 17:13:49 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*parsing(char *cmd, char **envp, int *perm_error)
{
	char	**path;
	char	*cmd_path;
	size_t	i;

	path = init_path_dirs(envp);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		cmd_path = build_cmd_path(cmd, path[i]);
		if (!cmd_path)
			return (free_matrix(path), NULL);
		if (is_executable_path(cmd_path, perm_error))
			return (free_matrix(path), cmd_path);
		errno = 0;
		free(cmd_path);
		i++;
	}
	return (free_matrix(path), NULL);
}

static void	exec_with_env(char *path, char **argv, char **env, int free_path)
{
	char	**exec_env;

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
	if (errno == ENOENT)
		exit_with_error(argv[0], 127);
	if (errno == EACCES || errno == EISDIR 
		|| errno == ENOEXEC || errno == ENOTDIR) 
		exit_with_error(argv[0], 126);
	exit_with_error(argv[0], EXIT_FAILURE);
}

void	execute_external(char **cmd_argv, char **env)
{
	char	*cmd_path;
	int		perm_error;

	if (ft_strchr(cmd_argv[0], '/'))
	{
		check_is_dir(cmd_argv[0]);
		exec_with_env(cmd_argv[0], cmd_argv, env, 0);
	}
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
