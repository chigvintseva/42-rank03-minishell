/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_fill_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:36:30 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/27 17:32:46 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_quote_fill(t_lexer *input, int *inside)
{
	if (input->s[input->i] == '"' && *inside != 2)
	{
		if (*inside == 0)
			*inside = 1;
		else if (*inside == 1)
			*inside = 0;
		input->i++;
		return (1);
	}
	if (input->s[input->i] == '\'' && *inside != 1)
	{
		if (*inside == 0)
			*inside = 2;
		else if (*inside == 2)
			*inside = 0;
		input->i++;
		return (1);
	}
	return (0);
}

void	copy_value(char *word, size_t *k, char *value)
{
	size_t	i;

	if (!value)
		return ;
	i = 0;
	while (value[i])
	{
		word[*k] = value[i];
		(*k)++;
		i++;
	}
}

void	copy_status(char *word, size_t *k, int status)
{
	char	*tmp;
	size_t	i;

	tmp = ft_itoa(status);
	if (!tmp)
		return ;
	i = 0;
	while (tmp[i])
	{
		word[*k] = tmp[i];
		(*k)++;
		i++;
	}
	free(tmp);
}

void	fill_dollar_var(char *word, size_t *k,
	t_lexer *input, t_shell *shell)
{
	size_t	start;
	size_t	len;
	char	*value;

	start = input->i + 1;
	len = 0;
	while (is_var_char(input->s[start + len]))
		len++;
	value = get_env_value(shell, input->s + start, len);
	copy_value(word, k, value);
	input->i = start + len;
}

void	fill_dollar(char *word, size_t *k,
	t_lexer *input, t_shell *shell)
{
	if (input->s[input->i + 1] == '?')
	{
		copy_status(word, k, shell->exit_status);
		input->i += 2;
		return ;
	}
	if (!is_var_start(input->s[input->i + 1]))
	{
		word[*k] = input->s[input->i];
		(*k)++;
		input->i++;
		return ;
	}
	fill_dollar_var(word, k, input, shell);
}
