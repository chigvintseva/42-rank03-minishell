/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:00:54 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/27 17:37:31 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_cmd_words(t_token *start, t_token *end)
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
			cur = cur->next;
		else if (cur->type == WORD)
			count++;
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (count);
}

static t_redir	*extract_redirs(t_token *start, t_token *end, int *error)
{
	t_token	*cur;
	t_redir	*head;

	*error = 0;
	cur = start;
	head = NULL;
	while (cur)
	{
		if (is_redir_token(cur->type))
		{
			head = process_single_redir(cur, end, head, error);
			if (*error)
			{
				if (errno == 0)
					errno = EINVAL;
				return (NULL);
			}
			cur = cur->next;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (head);
}

static char	**get_argv_and_redirs(t_token *start,
		t_token *end, int argc, t_redir **redirs)
{
	int		error;
	char	**argv;

	*redirs = extract_redirs(start, end, &error);
	if (error != 0)
	{
		if (errno == 0)
			errno = EINVAL;
		return (NULL);
	}
	argv = extract_argv(start, end, argc);
	if (!argv)
	{
		if (*redirs)
			free_redirs(*redirs);
		*redirs = NULL;
	}
	return (argv);
}

static int	prepare_argv_and_redirs(t_token *start, t_token *end, 
		t_cmd_parts *parts)
{
	int		error;

	if (parts->argc == 0)
	{
		parts->redirs = extract_redirs(start, end, &error);
		if (error != 0)
		{
			if (errno == 0)
				errno = EINVAL;
			return (0);
		}
		parts->argv = NULL;
	}
	else if (parts->argc > 0)
	{
		parts->argv = get_argv_and_redirs(start, end, parts->argc,
				&parts->redirs);
		if (!(parts->argv))
			return (0);
	}
	return (1);
}

t_cmd	*build_cmd(t_token *start, t_token *end)
{
	t_cmd_parts	parts;
	t_cmd		*cmd;

	if (start == NULL || end == NULL || token_in_range(start, end, end) == 0)
	{
		errno = EINVAL;
		return (NULL);
	}
	parts.argv = NULL;
	parts.redirs = NULL;
	parts.argc = count_cmd_words(start, end);
	if (parts.argc < 0 || !(prepare_argv_and_redirs(start, end, &parts)))
	{
		if (errno == 0)
			errno = EINVAL;
		return (NULL);
	}
	cmd = new_cmd(parts.argv, parts.argc, parts.redirs);
	if (!cmd)
	{
		free_argv(parts.argv);
		free_redirs(parts.redirs);
	}
	return (cmd);
}
