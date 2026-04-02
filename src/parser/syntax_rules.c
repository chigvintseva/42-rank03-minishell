/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:10 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/03 00:25:17 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	syntax_rules(t_token *lst, t_token **bad_token)
{
	if (lst == NULL)
		return (0);
	if (lst->type == PIPE)
		return (*bad_token = lst, 0);
	while (lst->next != NULL)
	{
		if (lst->type == PIPE && lst->next->type == PIPE)
			return (*bad_token = lst->next, 0);
		if (is_redir_token(lst->type) == 1 
			&& is_word_token(lst->next->type) == 0)
			return (*bad_token = lst->next, 0);
		lst = lst->next;
	}
	if (lst->type == PIPE || is_redir_token(lst->type))
		return (*bad_token = NULL, 0);
	return (1);
}

t_token	*syntax_error_token(t_token *lst)
{
	t_token	*bad_token;

	bad_token = NULL;
	if (syntax_rules(lst, &bad_token) == 0)
		return (bad_token);
	return (NULL);
}

int	is_syntax_valid(t_token *lst)
{
	t_token	*bad_token;

	bad_token = NULL;
	if (syntax_rules(lst, &bad_token) == 0)
		return (0);
	return (1);
}
