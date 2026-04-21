/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:24:12 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/21 19:07:54 by achigvin         ###   ########.fr       */
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
