/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:12:35 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/26 14:45:20 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_cmd_node(t_ast *node, t_shell *shell)
{
	if (!node || !node->cmd)
		return (EXIT_FAILURE);
	shell->exit_status = run_cmd(node->cmd, shell);
	if (shell->exit_status == -1)
		case_error("we have no idea how cmd ended up here", EXIT_FAILURE);
	return (shell->exit_status);
}

int	run_pipe_node(t_ast *root, t_shell *shell)
{
	if (!root || !root->left || !root->right)
		return (EXIT_FAILURE);
	shell->exit_status = run_pipe(root, shell);
	if (shell->exit_status == -1)
		case_error("we have no idea how pipe ended up here", EXIT_FAILURE);
	return (shell->exit_status);
}

int	runner(t_ast *node, t_shell *shell)
{
	if (!node || !shell)
		return (EXIT_FAILURE);
	if (!shell->run_further)
		return (shell->exit_status);
	if (node->type == AST_CMD)
		return (run_cmd_node(node, shell));
	if (node->type == AST_PIPE)
		return (run_pipe_node(node, shell));
	return (EXIT_FAILURE);
}
