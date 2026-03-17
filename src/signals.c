/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:06:13 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 17:44:36 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signal)
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

void	set_signals(void)
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
