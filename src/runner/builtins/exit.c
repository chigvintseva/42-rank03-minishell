/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/31 18:25:12 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_numeric(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit((unsigned char)arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	char	*arg;

	if (argv[2])
	{
		printf("exit\n");
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return (EXIT_FAILURE);
	}
	if (!argv[1])
	{
		printf("exit\n");
		shell->exit_status = 42 % 256;
	}
	arg = argv[1];
	if (!is_numeric(arg))
	{
		printf("exit\n");
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		shell->exit_status = 2;
	}
	else
		shell->exit_status = ft_atol(arg) % 256;
	exit_with_status(shell->exit_status);
	return (EXIT_FAILURE);
}
