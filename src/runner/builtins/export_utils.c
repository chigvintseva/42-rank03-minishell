/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:29:32 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/01 15:49:07 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

size_t	env_len(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

char	**dup_env(char **env)
{
	char	**env_copy;
	size_t	i;
	size_t	len;

	len = env_len(env);
	env_copy = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
			return (free_env_copy(env_copy, i), NULL);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

char	**sort_env(char **copy)
{
	char	*temp;
	size_t	i;
	size_t	swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (copy[i] && copy[i + 1])
		{
			if (ft_strcmp(copy[i], copy[i + 1]) > 0)
			{
				temp = copy[i];
				copy[i] = copy[i + 1];
				copy[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
	return (copy);
}

static void	print_export_line(char *entry)
{
	size_t	j;

	j = 0;
	printf("declare -x ");
	while (entry[j] && entry[j] != '=')
	{
		printf("%c", entry[j]);
		j++;
	}
	if (!entry[j])
	{
		printf("\n");
		return ;
	}
	printf("=\"%s\"\n", entry + j + 1);
}

void	sorted_print(char **sorted)
{
	size_t	i;

	i = 0;
	while (sorted[i])
	{
		print_export_line(sorted[i]);
		i++;
	}
}
