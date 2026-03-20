/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:12:35 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/20 21:53:39 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_cmd_node(t_ast *node, t_shell *shell)
{
	if (!node || !node->cmd)
		return (1);
	shell->exit_status = run_cmd(node->cmd, shell); // sasha's runner - should do cmd and redirs
	return (shell->exit_status);
}

int	run_pipe_node(t_ast *root, t_shell *shell)
{
	if (!root || !root->left || !root->right)
		return (1);
	shell->exit_status = run_pipe(root, shell); // sasha's pipe executer
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
