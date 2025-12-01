/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:26:32 by achigvin          #+#    #+#             */
/*   Updated: 2025/11/13 21:20:13 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	size_t	i;

	result = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (((str[i] == '-') || (str[i] == '+')) && (ft_isdigit(str[i + 1]) == 1))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
