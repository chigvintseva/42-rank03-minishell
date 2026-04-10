/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:17:08 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/10 14:06:07 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	input_precheck(char *input)
{
	int	ret;

	ret = check_specialchars(input);
	if (ret == 1)
		return (errno = 0, case_error("Invalid character", 2));
	if (ret == 2)
		return (errno = 0,
			case_error("unexpected EOF while looking for matching `\"'", 2));
	return (EXIT_SUCCESS);
}

static int	tokenize_input(char *input, t_shell *shell, t_token **tokens)
{
    int	err;

    errno = 0;
    err = 0;
    *tokens = lexer(input, shell, &err);
    if (!*tokens)
    {
        errno = err;
        return (case_error("lexer", EXIT_FAILURE));
    }
    return (0);
}

static int	parse_input(t_ast **root, t_token *tokens)
{
	t_token	*bad_token;

	errno = 0;
	*root = parse_tokens(tokens);
	if (*root)
		return (0);
	if (errno != 0)
		return (case_error("parser", EXIT_FAILURE));
	bad_token = syntax_error_token(tokens);
	if (!bad_token)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(bad_token->value, 2);
		ft_putendl_fd("'", 2);
	}
	return (2);
}

static int	prepare_heredocs_ast(t_ast *root, t_shell *shell)
{
	int		status;

	if (!root || !shell)
		return (0);
	status = 0;
	if (root->type == AST_CMD && root->cmd)
	{
		status = handle_heredocs(root->cmd, shell);
		if (status != 0)
			return (status);
	}
	else if (root->type == AST_PIPE)
	{
		status = prepare_heredocs_ast(root->left, shell);
		if (status != 0)
			return (status);
		status = prepare_heredocs_ast(root->right, shell);
		if (status != 0)
			return (status);
	}
	return (0);
}

int	minishell(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_ast	*root;
	int		status;

	status = input_precheck(input);
	if (status != 0)
		return (status);
	status = tokenize_input(input, shell, &tokens);
	if (status != 0)
		return (status);
	status = parse_input(&root, tokens);
	if (status != 0)
		return (free_tokens(tokens), status);
	status = prepare_heredocs_ast(root, shell);
	if (status == 0)
		status = runner(root, shell);
	free_tokens(tokens);
	free_ast(root);
	return (status);
}
