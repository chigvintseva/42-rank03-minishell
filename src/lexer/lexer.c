/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:46:03 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 18:34:23 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *lexer(char *str)
{
	t_lexer	input;
	t_token	*new_token;

	if (!str)
		return (NULL);
	input.s = str;
	input.i = 0;
	input.tokens = NULL;
	while (input.s[input.i])
	{
		if (is_space(input.s[input.i]))
		{
			input.i++;
			continue;
		}
		if (is_operator(input.s[input.i]))
		{
			new_token = handle_operator(&input);
			if (!new_token) 
				return (free_tokens(input.tokens), NULL);
			if (tokenadd_back(&input.tokens, new_token) == -1)
				return (free_tokens(input.tokens), NULL);
			input.i++;
		}
		else
		{
			new_token = handle_word(&input);
			if (!new_token)
				return (free_tokens(input.tokens), NULL);
			if (tokenadd_back(&input.tokens, new_token) == -1)
				return (free_tokens(input.tokens), NULL);
		}
	}
	return (input.tokens);
}
