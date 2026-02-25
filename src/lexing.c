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

void	handle_operator(t_lexer *input)
{

}

void	handle_word(t_lexer *input)
{
	
}

void lexer(char *str)
{
	t_lexer	input;


	input.s = str;
	input.i = 0;
	while (input.s[input.i])
	{
		if (input.s[input.i] == ' ')
			input.i++;
		else if (input.s[input.i] == '|' || input.s[input.i] == '<' ||
												input.s[input.i] == '>')
			handle_operator(&input);
		else
			handle_word(&input);
	}

}