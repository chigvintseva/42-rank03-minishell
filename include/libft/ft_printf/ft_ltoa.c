/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:56:11 by achigvin          #+#    #+#             */
/*   Updated: 2025/09/06 21:25:15 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

static	int	ft_cnt(long n_cpy)
{
	unsigned long	cnt;

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

static	char	*ft_assign(int isneg, char *num, int digits, long n)
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

char	*ft_ltoa(long n)
{
	char	*num;
	int		isneg;
	int		digits;

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
