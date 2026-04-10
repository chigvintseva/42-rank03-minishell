/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/10 15:49:36 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	invalid_args(char **argv)
{
	if (!ft_strcmp(argv[1], "~") ||  !ft_strcmp(argv[1], "-") )
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": not supported argument", 2);
		return (EXIT_FAILURE);
	}
	if (argv[2])
		return (case_error("cd: too many arguments", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static char *get_env_var(char **env, const char *key)
{
	int i;
	size_t key_len;

	key_len = ft_strlen(key);
	for (i = 0; env[i]; i++)
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
	}
	return (NULL);
}

static int	resolve_cd_target(char **argv, char **env, char **path)
{
    if (!argv[1])
    {
        *path = get_env_var(env, "HOME");
        if (!*path)
            return (case_error("cd: HOME not set", EXIT_FAILURE));
    }
    else
    {
        *path = argv[1];
        if (invalid_args(argv))
            return (EXIT_FAILURE);
    }
    return (0);
}

int	builtin_cd(char **argv, char **env)
{
	char	*path;
	char	*cur_dir;

	if (resolve_cd_target(argv, env, &path) != 0)
		return (EXIT_FAILURE);
	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (case_error("cd: getcwd", EXIT_FAILURE));
	if (argv[1] && !ft_strcmp(argv[1], "."))
		return (update_env(env, "OLDPWD", cur_dir), free(cur_dir), EXIT_SUCCESS);
	if (chdir((const char *)path) != 0)
		return (free(cur_dir), cd_error(path));
	update_env(env, "OLDPWD", cur_dir);
	free(cur_dir);
	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (case_error("cd: getcwd", EXIT_FAILURE));
	return (update_env(env, "PWD", cur_dir), free(cur_dir), EXIT_SUCCESS);
}
