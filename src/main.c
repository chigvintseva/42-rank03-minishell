/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:43:06 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/11 16:43:06 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline

void	print_tokens(t_token *lst)
{
	while (lst)
	{
		printf("type: %d valuse: %s\n", lst->type, lst->value);
		lst = lst->next;
	}	
}

void	exit_with_error(char *msg, int code)
{
	if (errno)
		perror(msg);
	else
		printf("Error: %s\n", msg);
	exit(code);
}

int	main()
{
	char	*input;
	int		error;
	t_token	*tokens;

	input = readline("minishell$ "); // will be inside while(1) in amin nof minishell to get user's input
	if (!input)
		return (exit_with_error("Error", 1), 1);
	error = check_specialchars(input); // syntax check for uncloased " and symbols like ; && 
	if (error == 1)
		return (free(input), exit_with_error("Invalid character", 1), 1);
	if (error == 2)
		return (free(input), exit_with_error("Unclosed quotes", 1), 1);
	tokens = lexer(input);
	if (!tokens)
		return (free(input), exit_with_error("Error", 1), 1);
	print_tokens(tokens);
	free_tokens(tokens);
	free(input);
	return (0);
}
