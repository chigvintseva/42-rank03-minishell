/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/15 16:33:46 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_echo(char **argv)
{
	size_t	i;
	int		n_flag;

	n_flag = 0;
	i = 1;
	if (!argv[i])
		return (write (1, "\n", 1), EXIT_SUCCESS);
	while (!ft_strcmp(argv[i], "-n"))
	{
		i++;
		if (!argv[i])
			return (EXIT_SUCCESS);
	}
	if (i > 1)
		n_flag = 1;	
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (n_flag == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
