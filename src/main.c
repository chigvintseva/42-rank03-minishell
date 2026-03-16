/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:43:06 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/16 15:12:26 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline

int	minishell(char *input)
{
	int		error_input;
	t_token	*tokens;
	t_ast	*root;

	error_input = check_specialchars(input);
	if (error_input == 1 || 2)
		return (1);
	tokens = lexer(input);
	if (!tokens)
		return (1);
	root = parse_tokens(tokens);
	if (!root)
		return (1);
	return (runner(root));
}

int	main()
{
	char	*input;
	int		return_code;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (exit_with_error("Error", 1), 1);
		return_code = minishell(input);
		if (return_code == 1)
			return (free(input), exit_with_error("Error", 1), 1);
	}
	free(input);
	return (0);
}
