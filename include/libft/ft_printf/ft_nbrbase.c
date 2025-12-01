/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:56:21 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/30 18:58:09 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int	ft_nbrbase(unsigned long num, char *base, int fd)
{
	char			c;
	unsigned long	base_len;
	int				count;

	count = 0;
	base_len = ft_strlen(base);
	if (num < base_len)
	{
		c = base[num];
		ft_putchar_fd(c, fd);
		count++;
		return (count);
	}
	count += ft_nbrbase(num / base_len, base, 1);
	c = base[num % base_len];
	count++;
	ft_putchar_fd(c, fd);
	return (count);
}
