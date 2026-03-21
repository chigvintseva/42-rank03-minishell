/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:00:15 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 20:02:47 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*get_last_token(t_token *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

t_token	*find_last_pipe(t_token *start, t_token *end)
{
	if (start == NULL || end == NULL)
		return (NULL);
	while (end != NULL)
	{
		if (end->type == PIPE)
			return (end);
		if (end == start)
			break ;
		end = end->prev;
	}
	return (NULL);
}

int	is_redir_token(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == REDIR_APPEND)
		return (1);
	return (0);
}

int	is_word_token(t_token_type type)
{
	if (type == WORD)
		return (1);
	return (0);
}

int	token_in_range(t_token *start, t_token *end, t_token *target)
{
	if (start == NULL || target == NULL || end == NULL)
		return (0);
	while (start != NULL && start != end)
	{
		if (start == target)
			return (1);
		start = start->next;
	}
	if (start == target)
		return (1);
	return (printf("here\n"), 0);
}
