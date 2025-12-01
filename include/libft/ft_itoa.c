/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:32:58 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/22 13:32:59 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_cnt(int n_cpy)
{
	int	cnt;

	cnt = 0;
	if (n_cpy == 0)
		return (1);
	if (n_cpy < 0)
	{
		n_cpy = -n_cpy;
		cnt++;
	}
	while (n_cpy != 0)
	{
		cnt++;
		n_cpy = n_cpy / 10;
	}
	return (cnt);
}

static	char	*ft_assign(int isneg, char *num, int digits, int n)
{
	if (isneg == 1)
	{
		while (digits > 0)
		{
			num[digits] = (n % 10) + '0';
			digits--;
			n = n / 10;
		}
	}
	else
	{
		while (digits >= 0)
		{
			num[digits] = (n % 10) + '0';
			digits--;
			n = n / 10;
		}
	}
	return (num);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		isneg;
	int		digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = ft_cnt(n);
	num = (char *)malloc(digits + 1);
	if (!num)
		return (NULL);
	isneg = 0;
	if (n < 0)
	{
		n = -n;
		num[0] = '-';
		isneg = 1;
	}
	num[digits] = '\0';
	digits--;
	return (ft_assign(isneg, num, digits, n));
}
