/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:39:23 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 19:00:40 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline
#include <signal.h>

static volatile sig_atomic_t	g_signal;

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

int	minishell(t_shell *shell, char *input)
{
	t_token	*tokens;
	int		check_ret;
	t_ast	*root;

	check_ret = check_specialchars(input);
	if (check_ret == 1)
		return (case_error("Invalid character", 2), 2);
	if (check_ret == 2)
		return (case_error("Unclosed quotes", 2), 2);
	tokens = lexer(input);
	if (!tokens)
		return (ft_printf("Lexer error"), 2);
	root = parse_tokens(tokens);
	if (!root)
		return (free_tokens(tokens), case_error("Parser error", 2), 2);
	if (runner(root, shell))
		return (free_tokens(tokens), free_ast(root), case_error("Runner error", 2), 2);
	free_tokens(tokens);
	free_ast(root);
	return (0);
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (shell->run_further == 1)
	{
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
		input = readline("minishell$ ");
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			shell->run_further = 0;
		}
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
		case_error("Error ", 1);
		return (1);
	}
	set_signals();
	shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}
