/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/01 15:30:24 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_env(char **env, char **argv)
{
	size_t	i;
	char	**cleaned_env;

	cleaned_env = clean_env(env);
	if (!cleaned_env)
		return (EXIT_FAILURE);
	i = 0;
	if (argv[1] != NULL)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		return (free_matrix(cleaned_env), 127);
	}
	while (cleaned_env[i])
	{
		printf("%s\n", cleaned_env[i]);
		i++;
	}
	return (free_matrix(cleaned_env), EXIT_SUCCESS);
}
