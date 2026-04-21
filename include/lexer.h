/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:41:51 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 17:54:54 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	size_t	i;
	char 	*s;
	int		err;
	t_token	*tokens;
}	t_lexer;

t_token *lexer(char *str, t_shell *shell, int *err_out);

t_token	*handle_operator(t_lexer *input);

t_token	*handle_word(t_lexer *input, t_shell *shell);

int		is_word_end(char c, int inside);
int		is_var_start(char c);
int		is_var_char(char c);
size_t	status_len(int n);
char	*get_env_value(t_shell *shell, char *name, size_t len);

int		handle_quote_len(t_lexer *input, size_t *j, int *inside);
size_t	count_dollar_len(t_lexer *input, t_shell *shell, size_t *j);
void	count_one_part(t_lexer *input, t_shell *shell, size_t *j, size_t *len, int inside);
size_t	count_len(t_lexer *input, t_shell *shell);


int		handle_quote_fill(t_lexer *input, int *inside);
void	copy_value(char *word, size_t *k, char *value);
void	copy_status(char *word, size_t *k, int status);
void	fill_dollar_var(char *word, size_t *k, t_lexer *input, t_shell *shell);
void	fill_dollar(char *word, size_t *k, t_lexer *input, t_shell *shell);


int 	is_operator(char c);
int 	is_space(const char c);
int		check_specialchars(char *s);
t_token	*create_token(const char *value, t_token_type type, t_lexer *input);
int		tokenadd_back(t_token **lst, t_token *new);
void	free_tokens(t_token *lst);

#endif