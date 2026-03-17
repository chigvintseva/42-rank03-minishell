/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:43:06 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 13:32:44 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline

void	minishell(char *input, t_shell *shell)
{
	int		error_input;
	t_token	*tokens;
	t_ast	*root;

	error_input = check_specialchars(input);
	if (error_input == 1)
		return (ft_printf("Invalid character\n"), 1);
	if (error_input == 2)
		return (ft_printf("Unclosed quotes\n"), 1);
	tokens = lexer(input);
	if (!tokens)
		return (ft_printf("Lexer error\n"), 1);
	root = parse_tokens(tokens);
	if (!root)
		return (free_tokens(tokens), ft_printf("Parser error\n"), 1);
	if (!runner(root))
		return (free_tokens(tokens), free_ast(root), ft_printf("Runner error\n"), 1);
	return (0);
}

int	main(void)
{
	char	*input;
	t_shell	*shell;

	// init shell struct and signals
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (exit_with_error("Error", 1), 1);
		if (ft_strlen(input) == 0 || only_space(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		minishell(input, shell);
		free(input);
	}
	return (shell->exit_status);
}
