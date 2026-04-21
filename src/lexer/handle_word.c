/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:42:29 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/27 17:37:50 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	fill_one_part(char *word, size_t *k,
	t_lexer *input, t_shell *shell, int inside)
{
	if (input->s[input->i] == '$' && inside != 2)
		fill_dollar(word, k, input, shell);
	else
	{
		word[*k] = input->s[input->i];
		(*k)++;
		input->i++;
	}
}

static void	fill_word(char *word, t_lexer *input, t_shell *shell)
{
	size_t	k;
	int		inside;

	k = 0;
	inside = 0;
	while (!is_word_end(input->s[input->i], inside))
	{
		if (handle_quote_fill(input, &inside))
			continue ;
		fill_one_part(word, &k, input, shell, inside);
	}
	word[k] = '\0';
}

t_token	*handle_word(t_lexer *input, t_shell *shell)
{
	char	*word;
	size_t	len;
	t_token	*token;

	if (!input || !input->s || !shell)
		return (NULL);
	len = count_len(input, shell);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	fill_word(word, input, shell);
	token = create_token(word, WORD);
	free(word);
	return (token);
}
