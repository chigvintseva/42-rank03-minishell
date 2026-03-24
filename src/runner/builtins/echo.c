/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/24 17:47:18 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_echo(char **argv)
{
	size_t	i;
	if (!argv[1])
		return (write (1, "\n", 1), EXIT_SUCCESS);
	if (!ft_strcmp(argv[1], "-n"))
	{
		if (!argv[2])
			return (EXIT_SUCCESS);
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
			printf("%s", argv[i]);
			i++;
			if (argv[i])
				printf(" ");
		}
	}
	printf("\n");
	return (EXIT_SUCCESS);
}