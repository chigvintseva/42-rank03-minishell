/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:12:35 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/08 15:20:27 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_cmd_node(t_ast *node, t_shell *shell)
{
	if (!node || !node->cmd)
		return (errno = 0, case_error("runner: invalid cmd node", EXIT_FAILURE));
	shell->exit_status = run_cmd(node->cmd, shell);
	if (shell->exit_status == -1)
	{
		errno = 0;
		shell->exit_status = case_error("runner: unexpected cmd status", EXIT_FAILURE);
		return (shell->exit_status);
	}
	return (shell->exit_status);
}

int	run_pipe_node(t_ast *root, t_shell *shell)
{
	if (!root || !root->left || !root->right)
		return (errno = 0, case_error("runner: invalid pipe node", EXIT_FAILURE));
	shell->exit_status = run_pipe(root, shell);
	if (shell->exit_status == -1)
	{
		errno = 0;
		shell->exit_status = case_error("runner: unexpected pipe status", EXIT_FAILURE);
		return (shell->exit_status);
	}
	return (shell->exit_status);
}

int	runner(t_ast *node, t_shell *shell)
{
	if (!node || !shell)
		return (errno = 0, case_error("runner: invalid execution context", EXIT_FAILURE));
	if (!shell->run_further)
		return (shell->exit_status);
	if (node->type == AST_CMD)
		return (run_cmd_node(node, shell));
	if (node->type == AST_PIPE)
		return (run_pipe_node(node, shell));
	return (errno = 0, case_error("runner: unknown AST node type", EXIT_FAILURE));
}
