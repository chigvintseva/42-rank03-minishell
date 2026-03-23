/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:57:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 21:28:25 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_matrix(char **matrix)
{
	int	i;

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
	char	**envp_path;
	char	*cmd_path;
	size_t	i;

	envp_path = ft_split(find_path_env(envp), ':');
	if (!envp_path)
		return (NULL);
	i = 0;
	while (envp_path[i])
	{
		cmd_path = ft_strjoin(envp_path[i], "/");
		if (!cmd_path)
			return (free_matrix(envp_path), NULL);
		cmd_path = ft_realloc_join(cmd_path, cmd);
		if (!cmd_path)
			return (free_matrix(envp_path), NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (free_matrix(envp_path), cmd_path);
			else
				*perm_error = 1;
		}
		errno = 0;
		free(cmd_path);
		i++;
	}
	return (free_matrix(envp_path), NULL);
}
