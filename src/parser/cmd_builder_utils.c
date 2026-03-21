/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:20:41 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 20:02:49 by aleksandra       ###   ########.fr       */
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

t_redir	*redir_error(t_redir *head, int *error)
{
	*error = 1;
	free_redirs(head);
	return (NULL);
}
