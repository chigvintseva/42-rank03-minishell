/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:20:41 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/31 21:07:18 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == REDIR_IN)
		return (R_IN);
	if (type == REDIR_OUT)
		return (R_OUT);
	if (type == REDIR_APPEND)
		return (R_APPEND);
	return (R_HEREDOC);
}

void	redir_add_back(t_redir **head, t_redir *new_node)
{
	t_redir	*last;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

static t_redir	*redir_error(t_redir *head, int *error)
{
	*error = 1;
	free_redirs(head);
	return (NULL);
}
t_redir	*process_single_redir(t_token *cur, t_token *end, t_redir *head, int *error)
{
	t_redir	*new_node;

	if (cur == end || !cur->next)
		return (redir_error(head, error));
	new_node = new_redir(token_to_redir_type(cur->type), cur->next->value);
	if (!new_node)
		return (redir_error(head, error));
	redir_add_back(&head, new_node);
	return (head);
}

