#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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

// ast_builder
t_ast	*build_ast(t_token *start, t_token *end);

// cmd_builder_utils
t_redir_type	token_to_redir_type(t_token_type type);
void	redir_add_back(t_redir **head, t_redir *new_node);
t_redir	*redir_error(t_redir *head, int *error);

// cmd_argv
int	add_or_free_argv(char **argv, int i, t_token *c);
char	**extract_argv(t_token *start, t_token *end, int argc);

// cmd_builder
int	count_cmd_words(t_token *start, t_token *end);
t_redir	*process_single_redir(t_token *redir_token, t_token *end, t_redir *head, int *error);
t_redir	*extract_redirs(t_token *start, t_token *end, int *error);
char	**get_argv_and_redirs(t_token *start, t_token *end, int argc, t_redir **redirs);
t_cmd	*build_cmd(t_token *start, t_token *end);

// utils
t_token	*get_last_token(t_token *head);
t_token	*find_last_pipe(t_token *start, t_token *end);
int		is_redir_token(t_token_type type);
int		is_word_token(t_token_type type);
int		token_in_range(t_token *start, t_token *end, t_token *target);

// create_new
t_ast	*ast_new_pipe(void);
t_ast	*ast_new_cmd(t_cmd *cmd);
t_cmd	*new_cmd(char **argv, int argc, t_redir *redirs);
t_redir	*new_redir(t_redir_type type, char *target);

// syntax_rules
int	redir_rules(t_token *lst);
int pipe_rules(t_token *lst);
int	is_syntax_valid(t_token *lst);

// free_functions
void	free_redirs(t_redir *head);
void	free_argv(char **argv);
void	free_cmd(t_cmd *cmd);
void	free_ast(t_ast *root);
void	free_part_argv(char **argv, size_t filled);

#endif