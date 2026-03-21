/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:03 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 17:26:04 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_tokens(t_token *tokens)
{
	t_ast	*root;

	if (tokens == NULL)
		return (NULL);
	if (is_syntax_valid(tokens) == 0)
		return (NULL);
	root = build_ast(tokens, get_last_token(tokens));
	return (root);
}
