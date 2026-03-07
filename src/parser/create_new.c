/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:01:03 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/07 14:01:03 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_new_pipe(void)
{
	t_ast	*pipe_node;

	pipe_node = (t_ast *)malloc(sizeof(t_ast));
	if (!pipe_node)
		return (NULL);
	pipe_node->type = AST_PIPE;
	pipe_node->left = NULL;
	pipe_node->right = NULL;
	pipe_node->cmd = NULL;
	return (pipe_node);
}

t_ast	*ast_new_cmd(t_cmd *cmd)
{
	t_ast	*cmd_node;

	if (cmd == NULL)
		return (NULL);
	cmd_node = (t_ast *)malloc(sizeof(t_ast));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = AST_CMD;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	cmd_node->cmd = cmd;
	return (cmd_node);
}

t_cmd	*new_cm(char **argv, int argc, t_redir *redirs)
{

}

t_redir	*new_redir(t_redir_type type, char *target)
{

}
