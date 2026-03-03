//#include "minishell.c"

typedef struct s_lexer
{
	int		i;
	char 	*s;
}	t_lexer;

typedef enum e_token_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_APPEND,
	WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;

}	t_token;

int is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	handle_operator(t_lexer *input)
{
	if (input->s[input->i] == '|')
		; //create token
	else if (input->s[input->i] == '<')
	{
		if (input->s[input->i + 1] == '<')
		{
			; //create token
			input->i++;
		}
		else
			; //create token
	}
	else if (input->s[input->i]  == '>')
	{
		if (input->s[input->i + 1] == '>')
		{
			; //create token
			input->i++;
		}
		else
			; //create token
	}
	input->i++;
}
void	count_len(char *s, int *len)
{
	int	i;

	*len = 0;
	i = 0;
	while (!is_operator(s[i]) && !is_space(s[i]) && s[i])
	{
		if (s[i] != '"' && s[i] != 39)
		{
			(*len)++;
			i++;
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				(*len)++;
				i++;
			}
			if (s[i] != '"')
				; // return error
			i++;
		}
		if (s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39)
			{
				(*len)++;
				i++;
			}
			if (s[i] != 39)
				; // return error
			i++;
		}
	}
}

void	handle_word(t_lexer *input)
{
	char	*word;
	int		len;

	count_len(&(input->s[input->i]), &len);
	word = malloc((len * sizeof(char)) + 1);
	while (!is_operator(input->s[input->i]) && !is_space(input->s[input->i]) && input->s[input->i])
	{
		if (input->s[input->i] != '"' && input->s[input->i] == 39)
		{
			*word = input->s[input->i];
		}
		if (input->s[input->i] == '"')
		{
			input->i++;
			while (input->s[input->i])
			{	if (input->s[input->i] != '"')
					len++; 
				else
				{
					input->i++;
					break;
				}
				input->i++;
			}
			if (input->s[input->i - 1] != '"')
				;//return error
		}
		if (input->s[input->i] == 39)
		{
			input->i++;
			while (input->s[input->i])
			{	if (input->s[input->i] != 39)
					len++;
				else
				{
					input->i++;
					break;
				}
				input->i++;
			}
			if (input->s[input->i - 1] != 39)
				;//return error
		}
	}

}

void lexer(char *str)
{
	t_lexer	input;


	input.s = str;
	input.i = 0;
	while (input.s[input.i])
	{
		if (is_space(input.s[input.i]))
			input.i++;
		else if (is_operator(input.s[input.i]))
			handle_operator(&input);
		else
		{
			handle_word(&input);
			input.i++;
		}
	}

}
