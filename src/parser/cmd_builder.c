/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:00:54 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/07 14:00:54 by achigvin         ###   ########.fr       */
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
	while (cur != NULL)
	{
		if (is_redir_token(cur->type))
		{
			if (cur == end || cur->next == NULL)
				return (-1);
			cur = cur->next;
		}
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
	t_redir	*new_node;

	*error = 0;
	cur = start;
	head = NULL;
	while (cur != NULL)
	{
		if (is_redir_token(cur->type))
		{
			if (cur == end || cur->next == NULL)
				return (redir_error(head, error));
			new_node = new_redir(token_to_redir_type(cur->type),
					cur->next->value);
			if (new_node == NULL)
				return (redir_error(head, error));
			redir_add_back(&head, new_node);
			cur = cur->next;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (head);
}

static char	**extract_argv(t_token *start, t_token *end, int argc)
{
	t_token	*cur;
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	cur = start;
	i = 0;
	while (cur != NULL)
	{
		if (is_redir_token(cur->type))
		{
			if (cur == end || cur->next == NULL)
				return (free_part_argv(argv, i), NULL);
			cur = cur->next;
		}
		else if (cur->type == WORD)
		{
			argv[i] = ft_strdup(cur->value);
			if (!(argv[i]))
				return (free_part_argv(argv, i), NULL);
			i++;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (argv[i] = NULL, argv);
}

t_cmd	*build_cmd(t_token *start, t_token *end)
{
	char	**argv;
	t_redir	*redirs;
	t_cmd	*cmd;
	int		argc;
	int		error;

	if (start == NULL || end == NULL || token_in_range(start, end, end) == 0)
		return (NULL);
	argc = count_cmd_words(start, end);
	if (argc < 0)
		return (NULL);
	redirs = extract_redirs(start, end, &error);
	if (error != 0)
		return (NULL);
	argv = extract_argv(start, end, argc);
	if (!argv)
		return (free_redirs(redirs), NULL);
	cmd = new_cmd(argv, argc, redirs);
	if (cmd == NULL)
		return (free_argv(argv), free_redirs(redirs), NULL);
	return (cmd);
}
