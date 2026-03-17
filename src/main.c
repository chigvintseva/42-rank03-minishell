/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:39:23 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 16:23:21 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline

volatile sig_atomic_t	g_signal;

int init_shell(t_shell *shell, char **envp)
{
	char	**envp_copy;
	size_t	i;
	
	while (envp[i] != NULL)
		i++;
	envp_copy = (char **)malloc(sizeof(char *) * i);
	if (!envp_copy)
		return (1);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
			return (1);
		i++;
	}
	envp_copy[i] = NULL;
	shell->exit_status = 0;
	shell->run_further = 1;
	return (0);
}

void	shell_loop(t_shell *shell)
{

	
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				shell;

	if (init_shell(&shell, envp) == 1)
		return (exit_with_error("Error", 1), 1);
	set_signals();
	shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}
