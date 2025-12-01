/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrinput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:56:02 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/30 18:56:03 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

int	ft_ptrinput(long arg)
{
	int		count;
	char	*error_msg;

	error_msg = "(nil)";
	if (!arg)
	{
		ft_putstr_fd(error_msg, 1);
		return (ft_strlen(error_msg));
	}
	ft_putstr_fd("0x", 1);
	count = 2;
	count += ft_nbrbase(arg, "0123456789abcdef", 1);
	return (count);
}
