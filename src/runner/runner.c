/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:12:35 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 20:45:54 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_cmd_node(t_ast *node, t_shell *shell)
{
	if (!node || !node->cmd)
		return (1);
	shell->exit_status = run_cmd(node->cmd, shell);
	if (shell->exit_status == -1)
		case_error("we have no idea how cmd ended up here", 1);
	return (shell->exit_status);
}

int	run_pipe_node(t_ast *root, t_shell *shell)
{
	if (!root || !root->left || !root->right)
		return (1);
	shell->exit_status = run_pipe(root, shell);
	if (shell->exit_status == -1)
		case_error("we have no idea how pipe ended up here", 1);
	return (shell->exit_status);
}

int	runner(t_ast *node, t_shell *shell)
{
	if (!node || !shell)
		return (1);
	if (!shell->run_further)
		return (shell->exit_status);
	if (node->type == AST_CMD)
		return (run_cmd_node(node, shell));
	if (node->type == AST_PIPE)
		return (run_pipe_node(node, shell));
	return (1);
}
