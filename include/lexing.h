#ifndef LEXING_H
# define LEXING_H

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

int is_operator(char c);
int is_space(char c);

#endif