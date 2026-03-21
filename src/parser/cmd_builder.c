/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:00:54 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 18:06:10 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_cmd_words(t_token *start, t_token *end)
{
	t_token	*cur;
	int		count;

	if (start == NULL || end == NULL)
		return (-1);
	cur = start;
	count = 0;
	while (cur)
	{
		if (is_redir_token(cur->type))
			break ;
		else if (cur->type == WORD)
			count++;
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (count);
}

t_redir	*process_single_redir(t_token *cur,	t_redir *head)
{
	t_redir	*new_node;

	new_node = new_redir(token_to_redir_type(cur->type), cur->next->value);
	if (!new_node)
		return (NULL);
	redir_add_back(&head, new_node);
	return (head);
}

t_redir	*extract_redirs(t_token *start, t_token *end)
{
	t_token	*cur;
	t_redir	*head;

	cur = start;
	head = NULL;
	while (cur)
	{
		if (is_redir_token(cur->type))
		{
			head = process_single_redir(cur, head);
			if (!head)
				return (NULL);
			cur = cur->next;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (head);
}

static int have_redirs(t_token *start, t_token *end)
{
	t_token *cur;

	cur = start;
	while (cur != end)
	{
		if (is_redir_token(cur->type))
			return (1);
		cur = cur->next;
	}
	return (0);
}

char	**get_argv_and_redirs(t_token *start, t_token *end, int argc, t_redir **redirs)
{
	char	**argv;

	if (have_redirs(start, end))
	{
		*redirs = extract_redirs(start, end);
		if (!(*redirs))
			return (NULL);	
	}
	argv = extract_argv(start, end, argc);
	if (!argv)
	{
		if (*redirs)
			free_redirs(*redirs);
	}
	return (argv);
}

t_cmd	*build_cmd(t_token *start, t_token *end)
{
	int		argc;
	t_redir	*redirs;
	char	**argv;
	t_cmd	*cmd;

	if (start == NULL || end == NULL || token_in_range(start, end, end) == 0)
		return (NULL);
	argc = count_cmd_words(start, end);
	if (argc <= 0)
		return (NULL);
	argv = get_argv_and_redirs(start, end, argc, &redirs);
	if (!argv)
		return (printf("----------failed argv\n\n"), NULL);
	cmd = new_cmd(argv, argc, redirs);
	if (!cmd)
	{
		free_argv(argv);
		free_redirs(redirs);
	}
	return (cmd);
}
