/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/31 18:22:56 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (EXIT_FAILURE);
}

static int	add_env_entry(char ***env, char *new_entry)
{
	char	**new_env;
	size_t	i;
	size_t	len;

	len = env_len(*env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (free(new_entry), case_error("add_env_entry", EXIT_FAILURE));
	i = 0;
	while (i < len)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (EXIT_SUCCESS);
}

static int	replace_env_entry(char **env, int idx, char *new_entry)
{
	if (!env || idx < 0 || !new_entry)
		return (EXIT_FAILURE);
	free(env[idx]);
	env[idx] = new_entry;
	return (EXIT_SUCCESS);
}

static char	*dup_key_only(char *arg)
{
	size_t	len;
	char	*key;

	len = key_len(arg);
	key = ft_substr(arg, 0, len);
	return (key);
}

static int	export_one(char *arg, t_shell *shell)
{
	int		idx;
	char	*new_entry;

	if (!is_valid_identifier(arg))
		return (export_error(arg));
	idx = find_env_key(shell->env, arg);
	if (!has_equal(arg))
	{
		if (idx != -1)
			return (EXIT_SUCCESS);
		new_entry = dup_key_only(arg);
		if (!new_entry)
			return (case_error("ft_substr in dup_key_only", EXIT_FAILURE));
		return (add_env_entry(&(shell->env), new_entry));
	}
	new_entry = ft_strdup(arg);
	if (!new_entry)
		return (case_error("ft_strdup in export_one", EXIT_FAILURE));
	if (idx != -1)
		return (replace_env_entry(shell->env, idx, new_entry));
	return (add_env_entry(&(shell->env), new_entry));
}

int	builtin_export(char **argv, t_shell *shell)
{
	char **env_copy;
	int		ret;
	size_t	i;

	if (!argv[1])
	{
		env_copy = dup_env(shell->env);
		if (!env_copy)
			return (case_error("malloc in dup_env", EXIT_FAILURE));
		env_copy = sort_env(env_copy);
		sorted_print(sort_env(env_copy));
		free_matrix(env_copy);
		return (EXIT_SUCCESS);
	}
	ret = EXIT_SUCCESS;
	i = 1;
	while (argv[i])
	{
		ret = export_one(argv[i], shell);
		i++;
	}
	return (ret);
}
