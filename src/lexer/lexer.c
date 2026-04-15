/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:46:03 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/15 16:16:19 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_lexer(t_lexer *input, char *str)
{
	input->s = str;
	input->i = 0;
	input->err = 0;
	input->tokens = NULL;
}

static int	process_operator_token(t_lexer *input, int *err_out)
{
	t_token	*new_token;

	new_token = handle_operator(input);
	if (!new_token)
	{
		if (input->err == 0)
			input->err = EINVAL;
		free_tokens(input->tokens);
		*err_out = input->err;
		return (0);
	}
	if (!tokenadd_back(&input->tokens, new_token))
	{
		if (input->err == 0)
			input->err = EINVAL;
		free_tokens(input->tokens);
		*err_out = input->err;
		return (0);
	}
	return (1);
}

static int	process_word_token(t_lexer *input, int *err_out, t_shell *shell)
{
	t_token	*new_token;

	new_token = handle_word(input, shell);
	if (!new_token)
	{
		if (input->err == 0)
			input->err = EINVAL;
		free_tokens(input->tokens);
		*err_out = input->err;
		return (0);
	}
	if (!tokenadd_back(&input->tokens, new_token))
	{
		if (input->err == 0)
			input->err = EINVAL;
		free_tokens(input->tokens);
		*err_out = input->err;
		return (0);
	}
	return (1);
}

t_token *lexer(char *str, t_shell *shell, int *err_out)
{
	t_lexer	input;

	if (!str || !shell)
		return (*err_out = EINVAL, NULL);
	init_lexer(&input, str);
	while (input.s[input.i])
	{
		if (is_space(input.s[input.i]))
		{
			input.i++;
			continue ;
		}
		if (is_operator(input.s[input.i]))
		{
			if (!process_operator_token(&input, err_out))
				return (NULL);
			input.i++;
		}
		else
		{
			if (!process_word_token(&input, err_out, shell))
				return (NULL);
		}
	}
	return (input.tokens);
}
