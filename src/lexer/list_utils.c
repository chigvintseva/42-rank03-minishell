/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:42:33 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/09 21:02:38 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(const char *value, t_token_type type, t_lexer *input)
{
	t_token	*token;
	char	*dup_value;

	if (!value || !input)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (input->err = errno, NULL);
	dup_value = ft_strdup(value);
	if (!dup_value)
		return (free(token), input->err = errno, NULL);
	token->type = type;
	token->value = dup_value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

int	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return (0);
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (1);
}

void	free_tokens(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->value);
		free(tmp);
	}
}
