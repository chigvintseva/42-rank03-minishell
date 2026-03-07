/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:00:15 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/07 14:00:15 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*get_last_token(t_token *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int	is_redir_token(t_token_type type)
{

}

int	is_word_token(t_token_type type)
{

}

int		token_in_range(t_token *start, t_token *end, t_token *target)
{

}
