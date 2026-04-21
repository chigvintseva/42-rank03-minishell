/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:57:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 00:10:19 by achigvin         ###   ########.fr       */
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
	matrix = NULL;
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

static char *create_cmd_path(char *env_path, char *cmd)
{
	char *cmd_path;

	cmd_path = ft_strjoin(env_path, "/");
	if (!cmd_path)
		return (NULL);
	cmd_path = ft_realloc_join(cmd_path, cmd);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

static char *find_executable(char **envp_path, char *cmd, int *perm_error)
{
	char *cmd_path;
	size_t i;

	i = 0;
	while (envp_path[i])
	{
		cmd_path = create_cmd_path(envp_path[i], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			else
				*perm_error = 1;
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char *parsing(char *cmd, char **envp, int *perm_error)
{
	char **envp_path;
	char *cmd_path;

	envp_path = ft_split(find_path_env(envp), ':');
	if (!envp_path)
		return (NULL);
	cmd_path = find_executable(envp_path, cmd, perm_error);
	free_matrix(envp_path);
	return (cmd_path);
}
