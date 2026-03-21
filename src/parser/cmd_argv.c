/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:06:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 17:15:11 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_issue(t_token *cur, t_token *end)
{
	cur = cur->next->next;
	while (cur != end)
	{
		if (is_redir_token(cur->type))
			cur = cur->next->next;
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
	while (cur != end)
	{
		if (is_word_token(cur->type))
		{
			argv[i] = ft_strdup(cur->value);
			if (!argv[i])
				return (free_part_argv(argv, i), NULL);
			i++;
			cur = cur->next;
		}
		else if (is_redir_token(cur->type))
		{
			if (redir_issue(cur, end))
				return (free_part_argv(argv, i), NULL);
			break ;
		}
	}
	return (argv[i] = NULL, argv);
}
