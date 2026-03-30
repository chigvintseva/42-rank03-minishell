/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/27 17:38:37 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	cd_error(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
}

static int	invalid_args(char **argv)
{
	if (!ft_strcmp(argv[1], "~") ||  !ft_strcmp(argv[1], "-") )
		return (cd_error(argv[1]), case_error("Not supported argument", EXIT_FAILURE));
	if (argv[2])
		return (case_error("minishell: cd: too many arguments", EXIT_FAILURE));
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

static void update_env(char **env, const char *key, const char *value)
{
	int i;
	size_t key_len;
	char *new_var;

	key_len = ft_strlen(key);
	for (i = 0; env[i]; i++)
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
		{
			free(env[i]);
			new_var = ft_strjoin(ft_strjoin(key, "="), value);
			env[i] = new_var;
			return;
		}
	}
}

int	builtin_cd(char **argv, char **env)
{
	char	*path;
	char	*cur_dir;

	if (!argv[1])
	{
		path = get_env_var(env, "HOME");
		if (!path)
			return (case_error("minishell: cd: HOME not set", EXIT_FAILURE));
	}
	if (invalid_args(argv))
		return (EXIT_FAILURE);
	path = argv[1];
	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (case_error("getcwd failed", EXIT_FAILURE));
	if (!ft_strcmp(argv[1], "."))
		return (update_env(env, "OLDPWD", cur_dir), free(cur_dir), EXIT_SUCCESS);
	if (chdir((const char *)path) != 0)
		return (free(cur_dir), cd_error(argv[1]), case_error("", EXIT_FAILURE));
	update_env_var(env, "OLDPWD", cur_dir);
	free(cur_dir);
	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (case_error("getcwd failed", EXIT_FAILURE));
	return (update_env(env, "PWD", cur_dir), free(cur_dir), EXIT_SUCCESS);
}
