/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:41:51 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 18:34:15 by achigvin         ###   ########.fr       */
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
	int		i; // index in a str form input
	char 	*s; // string form input
	t_token	*tokens;
}	t_lexer;

t_token *lexer(char *str);
int 	is_operator(char c);
int 	is_space(const char c);
int		check_specialchars(char *s);
t_token	*create_token(const char *value, t_token_type type);
int		tokenadd_back(t_token **lst, t_token *new);
void	free_tokens(t_token *lst);

#endif