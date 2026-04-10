/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:34:15 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/10 15:50:53 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	cd_error(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(arg);
	errno = 0;
	return (EXIT_FAILURE);
}

void	update_env(char **env, const char *key, const char *value)
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

