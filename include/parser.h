#ifndef PARSER_H
# define PARSER_H

typedef enum	e_ast_type
{
	AST_CMD,
	AST_PIPE
}	t_ast_type;

typedef enum	e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;


typedef struct s_cmd
{
	char	**argv;
	int		argc;
	t_redir	*redirs;
}	t_cmd;

typedef struct s_ast
{
	t_ast_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd			*cmd;
}	t_ast;

// parser
t_ast	*parse_tokens(t_token *tokens);


// utils
t_token	*get_last_token(t_token *head);
int		is_redir_token(t_token_type type);
int		is_word_token(t_token_type type);
int		token_in_range(t_token *start, t_token *end, t_token *target);
// create_new
t_ast	*ast_new_cmd(t_cmd *cmd);
t_ast	*ast_new_pipe(void);
t_cmd	*new_cmd(char **argv, int argc, t_redir *redirs);
t_redir	*new_redir(t_redir_type type, char *target);



int	validate_syntax(t_token *tokens);
int	check_pipe_syntax(t_token *token);
int	check_redir_syntax(t_token *token);

#endif