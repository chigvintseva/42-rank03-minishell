/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:59:19 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/15 16:20:11 by achigvin         ###   ########.fr       */
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

int	key_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

int	has_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_identifier(char *arg)
{
	size_t	i;

	if (!arg || !arg[0])
		return (0);
	if (!(ft_isalpha((unsigned char)arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum((unsigned char)arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	find_env_key(char **env, char *arg)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	len = i;
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], arg, len)
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
