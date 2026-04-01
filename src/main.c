/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:39:23 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 00:08:38 by achigvin         ###   ########.fr       */
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

static void	set_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = signal_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
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
	char	buffer[1024];
	char	*input;
	size_t	len;

	while (shell->run_further == 1)
	{
		update_sigint_status(shell);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
			shell->run_further = 0;
		else
		{
			len = ft_strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n')
				buffer[len - 1] = '\0';
			if (ft_strlen(buffer) == 0 || only_space(buffer))
			{
				/* do nothing, just continue */
			}
			else
			{
				input = ft_strdup(buffer);
				if (input)
				{
					shell->exit_status = minishell(input, shell);
					free(input);
				}
			}
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
		shell.exit_status = case_error("Shell Initialisation Error ", 1);
		return (shell.exit_status);
	}
	set_signals();
	shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}
