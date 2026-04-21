/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:03 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 21:38:30 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_tokens(t_token *start)
{
	t_ast	*root;
	t_token *end;

	end = get_last_token(start);
	if (start == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	if (!is_syntax_valid(start))
	{
		errno = 0;
		return (NULL);
	}
	root = build_ast(start, end);
	if (!root && errno == 0)
		errno = EINVAL;
	return (root);
}
