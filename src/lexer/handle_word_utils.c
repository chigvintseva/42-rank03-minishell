/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:24:44 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/27 17:27:56 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	is_word_end(char c, int inside)
{
	if (inside == 0 && (c == '\0' || is_space(c) || is_operator(c)))
		return (1);
	return (0);
}

int	is_var_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	is_var_char(char c)
{
	if (is_var_start(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

size_t	status_len(int n)
{
	size_t	len;
	long	nb;

	len = 1;
	nb = n;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*get_env_value(t_shell *shell, char *name, size_t len)
{
	size_t	i;

	if (!shell || !shell->env || !name || len == 0)
		return (NULL);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}
