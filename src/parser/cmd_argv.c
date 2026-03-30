/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:06:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/29 23:35:04 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			cur = cur->next;
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (argv[i] = NULL, argv);
}
