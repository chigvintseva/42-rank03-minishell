/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:03 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/07 14:01:03 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_tokens(t_token *tokens)
{
	t_ast	*root;

	if (is_syntax_valid(tokens) == 0)
		reutrn (NULL);
	
	root = build_ast(tokens);
	if (root = NULL)
		return (NULL);
	return (root);
}
