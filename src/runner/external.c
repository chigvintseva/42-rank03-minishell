/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:57:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/10 15:02:04 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_matrix(char **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static char	const *find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	**init_path_dirs(char **envp)
{
	char	*path_env;
	char	**path;

	path_env = (char *)find_path_env(envp);
	if (!path_env)
		return (errno = 0, NULL);
	path = ft_split(path_env, ':');
	if (!path)
	{
		if (errno == 0)
			errno = ENOMEM;
		return (NULL);
	}
	return (path);
}

static char	*build_cmd_path(char *cmd, char *dir)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(dir, "/");
	if (!cmd_path)
	{
		if (errno == 0)
			errno = ENOMEM;
		return (NULL);
	}
	cmd_path = ft_realloc_join(cmd_path, cmd);
	if (!cmd_path)
	{
		if (errno == 0)
			errno = ENOMEM;
		return (NULL);
	}
	return (cmd_path);
}

char	*parsing(char *cmd, char **envp, int *perm_error)
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
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (free_matrix(path), cmd_path);
			else
				*perm_error = 1;
		}
		errno = 0;
		free(cmd_path);
		i++;
	}
	return (free_matrix(path), NULL);
}
