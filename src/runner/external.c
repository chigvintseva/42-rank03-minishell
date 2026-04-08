/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:57:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/07 16:55:39 by aleksandra       ###   ########.fr       */
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

char	*parsing(char *cmd, char **envp, int *perm_error)
{
	char	**path;
	char	*cmd_path;
	char	*path_env;
	size_t	i;

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
	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], "/");
		if (!cmd_path)
		{
			if (errno == 0)
				errno = ENOMEM;
			return (free_matrix(path), NULL);
		}
		cmd_path = ft_realloc_join(cmd_path, cmd);
		if (!cmd_path)
		{
			if (errno == 0)
				errno = ENOMEM;
			return (free_matrix(path), NULL);
		}
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
