/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/02 00:06:37 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

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

void	cleanup_shell(t_shell *shell)
{
	if (shell->env)
	{
		free_matrix(shell->env);
		shell->env = NULL; // Nullify the pointer
	}
	// Clear readline history to free allocated memory
	rl_clear_history();
}

int	builtin_exit(char **argv, t_shell *shell)
{
	printf("exit\n");

	if (!argv[1])
	{
		shell->exit_status = 0;
		cleanup_shell(shell);
		exit_with_status(shell->exit_status);
	}
	else if (!is_numeric(argv[1]))
	{
		exit_error(argv[1]);
		shell->exit_status = 2;
		cleanup_shell(shell);
		exit_with_status(shell->exit_status);
	}
	else if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	else 
	{
		shell->exit_status = ft_atol(argv[1]) % 256;
		cleanup_shell(shell);
		exit_with_status(shell->exit_status);
	}
	return (shell->exit_status);	
}
