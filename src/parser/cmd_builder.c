/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:00:54 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/30 20:27:59 by aleksandra       ###   ########.fr       */
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
			cur = cur->next; // go to target
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
				return (NULL);
			cur = cur->next;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (head);
}
static char	**get_argv_and_redirs(t_token *start, t_token *end, int argc, t_redir **redirs)
{
	int		error;
	char	**argv;

	*redirs = extract_redirs(start, end, &error);
	if (error != 0)
		return (NULL);
	argv = extract_argv(start, end, argc);
	if (!argv)
	{
		if (*redirs)
			free_redirs(*redirs);
	}
	return (argv);
}

static int	prepare_argv_and_redirs(int argc, t_token *start, t_token *end, t_redir **redirs, char ***argv)
{
	int		error;

	if (argc == 0)
	{
		*redirs = extract_redirs(start, end, &error);
		if (error != 0)
 			return (0);
		*argv = NULL;
	}
	else if (argc > 0)
	{
		*argv = get_argv_and_redirs(start, end, argc, redirs);
		if (!(*argv))
			return (0);
	}
	return (1);
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
	if (argc < 0 || !(prepare_argv_and_redirs(argc, start, end, &redirs, &argv)))
		return (NULL);
	cmd = new_cmd(argv, argc, redirs);
	if (!cmd)
	{
		free_argv(argv);
		free_redirs(redirs);
	}
	return (cmd);
}
