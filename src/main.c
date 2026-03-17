/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:39:23 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 16:49:47 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline

volatile sig_atomic_t	g_signal;

int	minishell(t_shell *shell, char *input)
{
	t_token	*tokens;
	t_ast	*root;

	if (check_specialchars(input) == 1)
		return (ft_printf("Invalid character\n"), 1); // should i use printfs here? should i here set shell status maybe or what why
	if (check_specialchars(input) == 2)
		return (ft_printf("Unclosed quotes\n"), 1);
	tokens = lexer(input);
	if (!tokens)
		return (ft_printf("Lexer error\n"), 1);
	root = parse_tokens(tokens);
	if (!root)
		return (free_tokens(tokens), ft_printf("Parser error\n"), 1); // should i use printfs here? should i here set shell status maybe or what why
	if (!runner(root))
		return (free_tokens(tokens), free_ast(root), ft_printf("Runner error\n"), 1);
	return (0);
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (shell->run_further == 1)
	{
		input = readline("minishell$ ");
		if (fgets(input, sizeof(input), stdin) == NULL) // ctrl d case?
		{
			shell->run_further = 0;
			break ;
		}
		if (ft_strlen(input) == 0 || only_space(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		shell->exit_status = minishell(input, shell);
		if (shell->exit_status == 1)
			shell->run_further = 0;
		free(input);
	}
	
}

void	free_shell(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
}

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
	shell->env = envp_copy;
	shell->exit_status = 0;
	shell->run_further = 1;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (init_shell(&shell, envp) == 1)
		return (exit_with_error("Error", 1), 1);
	set_signals();
	shell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}
