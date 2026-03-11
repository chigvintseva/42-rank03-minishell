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

	pipe_node = malloc(sizeof(t_ast));
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
	cmd_node = malloc(sizeof(t_ast));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = AST_CMD;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	cmd_node->cmd = cmd;
	return (cmd_node);
}

t_cmd	*new_cmd(char **argv, int argc, t_redir *redirs)
{
	t_cmd	*new;

	if (argc < 0 || (argc > 0 && argv == NULL))
		return (NULL);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argc = argc;
	new->argv = argv;
	new->redirs = redirs;
	return (new);
}

t_redir	*new_redir(t_redir_type type, char *target)
{
	t_redir	*new;

	if (target == NULL)
		return (NULL);
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->target = ft_strdup(target);
	if (!(new->target))
		return (free(new), NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}
