/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_len_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:29:29 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/27 17:31:13 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote_len(t_lexer *input, size_t *j, int *inside)
{
	if (input->s[*j] == '"' && *inside != 2)
	{
		if (*inside == 0)
			*inside = 1;
		else if (*inside == 1)
			*inside = 0;
		(*j)++;
		return (1);
	}
	if (input->s[*j] == '\'' && *inside != 1)
	{
		if (*inside == 0)
			*inside = 2;
		else if (*inside == 2)
			*inside = 0;
		(*j)++;
		return (1);
	}
	return (0);
}

size_t	count_dollar_len(t_lexer *input, t_shell *shell, size_t *j)
{
	size_t	start;
	size_t	len;
	char	*value;

	if (input->s[*j + 1] == '?')
		return (*j += 2, status_len(shell->exit_status));
	if (!is_var_start(input->s[*j + 1]))
		return ((*j)++, 1);
	start = *j + 1;
	len = 0;
	while (is_var_char(input->s[start + len]))
		len++;
	value = get_env_value(shell, input->s + start, len);
	*j = start + len;
	if (!value)
		return (0);
	return (ft_strlen(value));
}

void	count_one_part(t_lexer *input, t_shell *shell,
	size_t *j, size_t *len, int inside)
{
	if (input->s[*j] == '$' && inside != 2)
		*len += count_dollar_len(input, shell, j);
	else
	{
		(*len)++;
		(*j)++;
	}
}

size_t	count_len(t_lexer *input, t_shell *shell)
{
	size_t	len;
	size_t	j;
	int		inside;

	len = 0;
	j = input->i;
	inside = 0;
	while (!is_word_end(input->s[j], inside))
	{
		if (handle_quote_len(input, &j, &inside))
			continue ;
		count_one_part(input, shell, &j, &len, inside);
	}
	return (len);
}
