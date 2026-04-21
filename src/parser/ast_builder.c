/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:18 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 20:02:52 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*build_cmd_node(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	t_ast	*node;

	cmd = build_cmd(start, end);
	if (cmd == NULL)
		return (NULL);
	node = ast_new_cmd(cmd);
	if (node == NULL)
		return (free_cmd(cmd), NULL);
	return (node);
}

static t_ast	*build_pipe_node(t_token *start, t_token *end, t_token *pipe)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = build_ast(start, pipe->prev);
	if (!left)
		return (NULL);
	right = build_ast(pipe->next, end);
	if (!right)
		return (free_ast(left), NULL);
	node = ast_new_pipe();
	if (!node)
		return (free_ast(left), free_ast(right), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*build_ast(t_token *start, t_token *end)
{
	t_token	*pipe;

	if (start == NULL || end == NULL 
		|| token_in_range(start, end, end) == 0)
		return (NULL);
	pipe = find_last_pipe(start, end);
	if (!pipe)
		return (build_cmd_node(start, end));
	return (build_pipe_node(start, end, pipe));
}
