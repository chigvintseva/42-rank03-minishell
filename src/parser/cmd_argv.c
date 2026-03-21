/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:06:25 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 20:02:50 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_or_free_argv(char **argv, int i, t_token *c)
{
	argv[i] = ft_strdup(c->value);
	if (!argv[i])
		return (-1);
	return (i + 1);
}

char	**extract_argv(t_token *start, t_token *end, int argc)
{
	char	**argv;
	t_token	*c;
	int		i;
	int		temp;
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	c = start;
	i = 0;
	while (c)
	{
		if (is_redir_token(c->type) && (c == end || !c->next))
			return (free_part_argv(argv, i), NULL);
		if (is_redir_token(c->type))
			c = c->next;
		else if (c->type == WORD && (temp = add_or_free_argv(argv, i, c)) < 0)
			return (free_part_argv(argv, i), NULL);
		else if (c->type == WORD)
			i = temp;
		if (c == end)
			return (argv[i] = NULL, argv);
		c = c->next;
	}
	return (argv);
}
