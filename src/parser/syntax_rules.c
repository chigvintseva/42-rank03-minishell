/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:10 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/30 20:26:27 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int pipe_rules(t_token *lst)
{
	if (lst == NULL)
		return (0);
	if (lst->type == PIPE)
		return (0);
	while (lst->next != NULL)
	{
		if (lst->type == PIPE && lst->next->type == PIPE)
			return (0);
		lst = lst->next;
	}
	if (lst->type == PIPE)
		return (0);
	return (1);
}

static int	redir_rules(t_token *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		if (is_redir_token(lst->type) == 1 
			&& is_word_token(lst->next->type) == 0)
			return (0);
		lst = lst->next;
	}
	if (is_redir_token(lst->type))
		return (0);
	return (1);
}

int	is_syntax_valid(t_token *lst)
{
	if (pipe_rules(lst) == 0)
		return (0);
	if (redir_rules(lst) == 0)
		return (0);
	return (1);
}
