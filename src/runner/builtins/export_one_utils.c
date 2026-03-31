/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:59:19 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/31 18:21:04 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

size_t	key_len(char *arg)
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

size_t	find_env_key(char **env, char *arg)
{
	size_t	i;
	size_t	len;

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
