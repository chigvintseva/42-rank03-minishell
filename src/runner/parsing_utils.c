/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:06:35 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/10 17:14:04 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**init_path_dirs(char **envp)
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

char	*build_cmd_path(char *cmd, char *dir)
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

static int	check_is_dir_path(char *cmd_path)
{
	struct stat	st;

	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

int	is_executable_path(char *cmd_path, int *perm_error)
{
	if (access(cmd_path, F_OK) != 0)
		return (0);
	if (check_is_dir_path(cmd_path))
		return (0);
	if (access(cmd_path, X_OK) == 0)
		return (1);
	*perm_error = 1;
	return (0);
}
