/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:17:08 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/27 17:36:50 by achigvin         ###   ########.fr       */
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
		return (free_tokens(tokens), case_error("minishell: syntax error near unexpected token", EXIT_FAILURE));
	status = runner(root, shell);
	free_tokens(tokens);
	free_ast(root);
	return (status);
}
