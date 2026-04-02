/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:46:03 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 18:08:03 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *lexer(char *str, t_shell *shell, int *err_out)
{
	t_lexer	input;
	t_token	*new_token;

	if (!str || !shell)
		return (*err_out = EINVAL, NULL);
	input.s = str;
	input.i = 0;
	input.err = 0;
	input.tokens = NULL;
	while (input.s[input.i])
	{
		if (is_space(input.s[input.i]))
		{
			input.i++;
			continue ;
		}
		if (is_operator(input.s[input.i]))
		{
			new_token = handle_operator(&input);
			if (!new_token)
			{
				if (input.err == 0)
					input.err = EINVAL;
				return (free_tokens(input.tokens), *err_out = input.err, NULL);
			}
			if (tokenadd_back(&input.tokens, new_token))
			{
				if (input.err == 0)
					input.err = EINVAL;
				return (free_tokens(input.tokens), *err_out = input.err, NULL);
			}
			input.i++;
		}
		else
		{
			new_token = handle_word(&input, shell);
			if (!new_token)
			{
				if (input.err == 0)
					input.err = EINVAL;
				return (free_tokens(input.tokens), *err_out = input.err, NULL);
			}
			if (tokenadd_back(&input.tokens, new_token))
			{
				if (input.err == 0)
					input.err = EINVAL;
				return (free_tokens(input.tokens), *err_out = input.err, NULL);
			}
		}
	}
	return (input.tokens);
}
