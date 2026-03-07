/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:00:58 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/07 14:00:58 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_redirs(t_redir *head)
{
	t_redir *temp;

	while (head != NULL)
	{
		free(head->target);
		temp = head;
		head = head->next;
		free(temp);
	}
}

void	free_argv(char **argv)
{
	size_t i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	
	free_argv(cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}

void	free_ast(t_ast *root)
{
	if (root == NULL)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	if (root->cmd != NULL)
		free_cmd(root->cmd);
	free(root);
}

void	free_part_argv(char **argv, size_t filled)
{
	size_t i;

	if (argv == NULL)
		return ;
	i = 0;
	while (i < filled)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
