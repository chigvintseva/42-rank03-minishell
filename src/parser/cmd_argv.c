/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:06:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/22 15:07:21 by aleksandra       ###   ########.fr       */
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

char	**extract_argv(t_token *cur, t_token *end, int argc)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (cur)
	{
		if (is_word_token(cur->type))
		{
			argv[i] = ft_strdup(cur->value);
			if (!argv[i])
				return (free_part_argv(argv, i), NULL);
			i++;
		}
		else if (is_redir_token(cur->type))
		{
			if (redir_issue(cur, end))
				return (free_part_argv(argv, i), NULL);
			break ;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (argv[i] = NULL, argv);
}
