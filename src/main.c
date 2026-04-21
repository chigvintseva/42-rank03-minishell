/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:39:23 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 14:48:56 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static volatile sig_atomic_t	g_signal;

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static int	set_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (sigemptyset(&sa_int.sa_mask) == -1)
		return (case_error("sigemptyset", EXIT_FAILURE));
	sa_int.sa_handler = signal_handler;
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (case_error("sigaction", EXIT_FAILURE));
	if (sigemptyset(&sa_quit.sa_mask) == -1)
		return (case_error("sigemptyset", EXIT_FAILURE));
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (case_error("sigaction", EXIT_FAILURE));
	return (0);
}

static void	update_sigint_status(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (shell->run_further == 1)
	{
		update_sigint_status(shell);
		input = readline("minishell$ ");
		if (input == NULL)
			shell->run_further = 0;
		else if (ft_strlen(input) == 0 || only_space(input))
			free(input);
		else
		{
			add_history(input);
			shell->exit_status = minishell(input, shell);
			free(input);
		}
	}	
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	g_signal = 0;
	errno = 0;
	if (init_shell(&shell, envp) != 0)
	{
		shell.exit_status = case_error("init_shell", EXIT_FAILURE);
		return (shell.exit_status);
	}
	if (set_signals() != 0)
	{
		free_shell(&shell);
		return (EXIT_FAILURE);
	}
	shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}
