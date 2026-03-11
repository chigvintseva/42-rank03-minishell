/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:10 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/07 14:01:10 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int pipe_rules(t_token *lst)
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

int	redir_rules(t_token *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		if (is_redir_token(lst->type) == 1 && is_word_token(lst->next->type) == 0)
			return (0);
		lst = lst->next;
	}
	if (is_redir_token(lst->type))
		return (0);
	return (1);
}
// ----------should be in lexer!!
// int	is_symbol_allowed(char *s1)
// {
// 	size_t	len;

// 	if (s1 == NULL)
// 		return (0);s
// 	len = ft_strlen(s1);
// 	if (len == 1)
// 	{
// 		if (ft_strncmp(s1, ";", len) == 0)
// 			return (0);
// 		if (ft_strncmp(s1, "\\", len) == 0)
// 			return (0);
// 		if (ft_strncmp(s1, "(", len) == 0)
// 			return (0);
// 		if (ft_strncmp(s1, ")", len) == 0)
// 			return (0);
// 	}
// 	if (len == 2)
// 	{
// 		if (ft_strncmp(s1, "&&", len) == 0)
// 			return (0);
// 		if (ft_strncmp(s1, "||", len) == 0)
// 			return (0);
// 	}
// 	return (1);
// }

// int	valid_symbols(t_token *lst)
// {
// 	if (lst == NULL)
// 		return (0);
// 	while (lst != NULL)
// 	{
// 		if (is_symbol_allowed(lst->value) == 0)
// 			return (0);
// 		lst = lst->next;
// 	}
// 	return (1);
// }

int	is_syntax_valid(t_token *lst)
{
	if (pipe_rules(lst) == 0)
		return (0);
	if (redir_rules(lst) == 0)
		return (0);
	return (1);
}
