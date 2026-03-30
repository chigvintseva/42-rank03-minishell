/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:54:49 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/25 17:38:21 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	find_to_rem(char **env, char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key) + 1;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0)
			return (printf("found in env\n"), i);
		i++;
	}
	return (-1);
}

static char	**remove_env_var(char **env, int to_rem)
{
	size_t	env_len;
	char	**new_env;
	size_t	i;
	size_t	j;

	env_len = 0;
	while(env[env_len])
		env_len++;
	new_env = malloc(sizeof(char *) * env_len);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i == to_rem)
			i++;
		new_env[j] = ft_strdup(env[i]);
		if (!new_env[j])
			return (free_matrix(new_env), NULL);
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (printf("removed\n"), free_matrix(env), new_env);
}

int	builtin_unset(char **argv, char ***env)
{
	int		to_rem;
	size_t	i;

	i = 1;
	while (argv[i])
	{
		to_rem = find_to_rem(*env, argv[i]);
		if (to_rem > 0)
			*env = remove_env_var(*env, to_rem);
		i++;
	}
	return (EXIT_SUCCESS);
}
