/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:17:08 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/31 21:04:35 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	input_precheck(char *input)
{
	int	ret;

	ret = check_specialchars(input);
	if (ret == 1)
		return (case_error("minishell: Invalid character", EXIT_FAILURE));
	if (ret == 2)
		return (case_error("minishell:  unexpected EOF while looking for matching `\"'", 2));
	return (EXIT_SUCCESS);
}

static int	prepare_heredocs_ast(t_ast *root, t_shell *shell)
{
	int		status;

	if (!root || !shell)
		return (0);
	status = 0;
	if (root->type == AST_CMD && root->cmd)
	{
		status = handel_heredocs(root->cmd, shell);
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
	errno = 0;
	tokens = lexer(input, shell);
	if (!tokens)
		return (case_error("minishell: lexer error", 1));
	root = parse_tokens(tokens);
	if (!root)
		return (free_tokens(tokens), case_error("minishell: syntax error near unexpected token", 1));
	status = prepare_heredocs_ast(root, shell);
	if (status == 0)
		status = runner(root, shell);
	free_tokens(tokens);
	free_ast(root);
	return (status);
}
