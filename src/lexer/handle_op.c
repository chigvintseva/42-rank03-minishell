/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:24:12 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 17:52:36 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *handle_operator(t_lexer *input)
{
	if (!input || !input->s)
		return (NULL);
	if (input->s[input->i] == '|')
		return (create_token("|", PIPE, input));
	else if (input->s[input->i] == '<')
	{
		if (input->s[input->i + 1] == '<')
		{
			input->i++;
			return (create_token("<<", HEREDOC, input));
		}
		else
			return (create_token("<", REDIR_IN, input));
	}
	else if (input->s[input->i] == '>')
	{
		if (input->s[input->i + 1] == '>')
		{
			input->i++;
			return (create_token(">>", REDIR_APPEND, input));
		}
		else
			return (create_token(">", REDIR_OUT, input));
	}
	return (NULL);
}
