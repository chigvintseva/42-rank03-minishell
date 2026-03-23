/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:06:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 21:53:42 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_issue(t_token *cur, t_token *end)
{
	if (end == NULL || cur == NULL)
		return (0);
	cur = cur->next;
	while (cur != end)
	{
		cur = cur->next;
		if (is_redir_token(cur->type))
			cur = cur->next;
		else
			return (1);
	}
	return (0);
}
static int	fill_argv(char **argv, t_token *cur, t_token *end, int *redir_break)
{
	int	i;

	i = 0;
	while (cur != end)
	{
		if (is_word_token(cur->type))
		{
			i = add_word(argv, i, cur);
			if (i < 0)
				return (-1);
		}
		else if (is_redir_token(cur->type))
		{
			if (redir_issue(cur, end))
				return (-1);
			*redir_break = 1;
			break ;
		}
		cur = cur->next;
	}
	return (i);
}

char	**extract_argv(t_token *cur, t_token *end, int argc)
{
	char	**argv;
	int		i;
	int		redir_break;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	redir_break = 0;
	i = fill_argv(argv, cur, end, &redir_break);
	if (i < 0)
		return (free_part_argv(argv, i), NULL);
	if (!redir_break)
		i = add_word(argv, i, end);
	if (i < 0)
		return (free_part_argv(argv, i), NULL);
	return (argv[i] = NULL, argv);
}
