/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:22:07 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/01 15:22:07 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	clean_env_len(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			len++;
		i++;
	}
	return (len);
}

char	**clean_env(char **env)
{
	char	**clean;
	int		i;
	int		j;

	clean = malloc(sizeof(char *) * (clean_env_len(env) + 1));
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			clean[j] = ft_strdup(env[i]);
			if (!clean[j])
				return (free_matrix(clean), NULL);
			j++;
		}
		i++;
	}
	clean[j] = NULL;
	return (clean);
}
