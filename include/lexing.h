#ifndef LEXING_H
# define LEXING_H

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
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	int		i;
	char 	*s;
	t_token	*tokens;
}	t_lexer;

t_token *lexer(char *str);
int 	is_operator(char c);
int 	is_space(char c);
t_token	*create_token(const char *value, t_token_type type);
void	tokenadd_back(t_token **lst, t_token *new);
void	free_tokens(t_token *lst);

#endif