#include "../include/minishell.h"

t_token	*handle_operator(t_lexer *input)
{
	if (input->s[input->i] == '|')
		return (create_token("|", PIPE)); //create token
	else if (input->s[input->i] == '<')
	{
		if (input->s[input->i + 1] == '<')
		{
			input->i++;
			return (create_token("<<", HEREDOC)); //create token
		}
		else
			return (create_token("<", REDIR_IN)); //create token
	}
	else if (input->s[input->i]  == '>')
	{
		if (input->s[input->i + 1] == '>')
		{
			input->i++;
			return (create_token(">>", REDIR_APPEND));  //create token
		}
		else
			return (create_token(">", REDIR_OUT));  //create token
	}
	return (NULL);
}

void handle_quotes(char quote, int *len, char **word, char *s, int *i)
{
		(*i)++;
		while (s[*i] && s[*i] != quote)
		{
			if(word)
				*(*word)++ = s[(*i)++];
			else
			{
				(*len)++;
				(*i)++;
			}
		}
		// if (s[*i] != quote)
		// 	exit_with_error("dquote>", 1); // return error
		(*i)++;
}

void	count_len(t_lexer *input, int *len)
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
			handle_quotes('"', len, 0, input->s, &tmp_i); //NULL
		if (input->s[tmp_i] == '\'')
			handle_quotes('\'', len, 0, input->s, &tmp_i); //NULL
	}
}

t_token	*handle_word(t_lexer *input)
{
	char	*word;
	int		len;
	char	*tmp;
	t_token	*token_word;

	count_len(input, &len); // check error		
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
	free(tmp);
	return (token_word);
}

t_token *lexer(char *str)
{
	t_lexer	input;
	t_token	*new_token;

	if (!str)
		return (NULL);
	input.s = str;
	input.i = 0;
	input.tokens = NULL;
	while (input.s[input.i])
	{
		if (is_space(input.s[input.i]))
			input.i++;
		if (is_operator(input.s[input.i]))
		{
			new_token = handle_operator(&input);
			if (!new_token) 
				return (NULL); // or ?
			tokenadd_back(&input.tokens, new_token);
			input.i++;
		}
		else
		{
			new_token = handle_word(&input);
			if (!new_token)
				return (NULL); // or ?
			tokenadd_back(&input.tokens, new_token);
		}
	}
	return (input.tokens);
}
