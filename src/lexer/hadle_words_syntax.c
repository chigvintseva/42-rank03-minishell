/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hadle_words_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:42:29 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/20 19:43:48 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*handle_operator(t_lexer *input)
{
	if (!input || !input->s)
		return (NULL);
	if (input->s[input->i] == '|')
		return (create_token("|", PIPE));
	else if (input->s[input->i] == '<')
	{
		if (input->s[input->i + 1] == '<')
		{
			input->i++;
			return (create_token("<<", HEREDOC));
		}
		else
			return (create_token("<", REDIR_IN));
	}
	else if (input->s[input->i]  == '>')
	{
		if (input->s[input->i + 1] == '>')
		{
			input->i++;
			return (create_token(">>", REDIR_APPEND));
		}
		else
			return (create_token(">", REDIR_OUT));
	}
	return (NULL);
}

void handle_quotes(char quote, int *len, char **word, char *s, int *i)
{
		(*i)++;
		while (s[*i] && s[*i] != quote)
		{
			if (word) 
				*(*word)++ = s[(*i)++];
			else
			{
				(*len)++;
				(*i)++;
			}
		}
		(*i)++;
}

static void	count_len(t_lexer *input, int *len)
{
	int	tmp_i;

	*len = 0;
	tmp_i = input->i;
	while (!is_operator(input->s[tmp_i]) && !is_space(input->s[tmp_i])
		&& input->s[tmp_i])
	{
		if (input->s[tmp_i] != '"' && input->s[tmp_i] != '\'')
		{
			(*len)++;
			tmp_i++;
		}
		if (input->s[tmp_i] == '"')
			handle_quotes('"', len, NULL, input->s, &tmp_i);
		if (input->s[tmp_i] == '\'')
			handle_quotes('\'', len, NULL, input->s, &tmp_i);
	}
}

t_token	*handle_word(t_lexer *input)
{
	char	*word;
	int		len;
	char	*tmp;
	t_token	*token_word;

	count_len(input, &len);
	word = malloc((len * sizeof(char)) + 1);
	if (!word)
		return (NULL);
	tmp = word;
	while (!is_operator(input->s[input->i]) && !is_space(input->s[input->i])
		&& input->s[input->i])
	{
		if (input->s[input->i] != '"' && input->s[input->i] != '\'')
			*word++ = input->s[input->i++];
		if (input->s[input->i] == '"')
			handle_quotes('"', 0, &word, input->s, &input->i);
		if (input->s[input->i] == '\'')
			handle_quotes('\'', 0, &word, input->s, &input->i);
	}
	*word = '\0';
	token_word = create_token(tmp, WORD);
	if (!token_word)
		return (free(tmp), NULL);
	return (free(tmp), token_word);
}
