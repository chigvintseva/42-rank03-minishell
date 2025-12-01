/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intinput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:55:36 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/30 18:55:38 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int	ft_intinput(int arg)
{
	char	*to_print;
	int		len;

	to_print = ft_itoa(arg);
	ft_putstr_fd(to_print, 1);
	len = (int)ft_strlen(to_print);
	free(to_print);
	return (len);
}

int	ft_uinput(unsigned long arg)
{
	int		len;
	char	*to_print;

	to_print = ft_ltoa(arg);
	ft_putstr_fd(to_print, 1);
	len = (int)ft_strlen(to_print);
	free(to_print);
	return (len);
}
