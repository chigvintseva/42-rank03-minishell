/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:12:35 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/18 18:49:22 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_cmd_node(t_ast *node, t_shell *shell)
{
	if (!node || !node->cmd)
	{
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	shell->exit_status = run_cmd(node->cmd, shell); // sasha's runner - should do cmd and redirs
	return (shell->exit_status);
}

int	run_pipe_node(t_ast *root, t_shell *shell)
{
	int	left_status;
	int	right_status;

	if (!root || !root->left || !root->right)
	{
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	left_status = runner(root->left, shell); // recursive, save status not output
	if (!shell->run_further)
		return (shell->exit_status);
	right_status = runner(root->right, shell); // recursive, save status not output
	if (!shell->run_further)
		return (shell->exit_status);
	shell->exit_status = run_pipe(root, shell, left_status, right_status); // sasha's pipe executer
	return (shell->exit_status);
}

int	runner(t_ast *node, t_shell *shell)
{
	if (!node || !shell)
		return (1); // ERROR
	if (!shell->run_further)
		return (shell->exit_status);
	if (node->type == AST_CMD)
		return (run_cmd_node(node, shell));
	if (node->type == AST_PIPE)
		return (run_pipe_node(node, shell));
	shell->exit_status = 1; // we got the type of node which we dont know
	return (shell->exit_status);
}
