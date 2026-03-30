/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/24 16:48:39 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	sorted_print(char **env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		
	}
}


int	builtin_export(char **agrv, t_shell *shell)
{
	if (!argv[1])
		return (sorted_print(env), EXIT_SUCCESS);
	else if (!key_value_pair(argv[1]))
	else if (key_value_pair(argv[1]))
	else
		return (case_error("minishell: export: ")
}