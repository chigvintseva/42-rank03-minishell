/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/24 16:04:50 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_exit(char **argv)
{
	size_t	i;
	if (!argv[1])
		return (write (1, "\n", 1), EXIT_SUCCESS); // or 1
	if (!ft_strcmp(argv[1], "-n"))
	{
		if (!argv[2])
			return (EXIT_SUCCESS); // or 1
		i = 2;
		while (argv[i])
		{
			printf("%s", argv[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			printf("%s\n", argv[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
