/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:55:24 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/30 18:55:25 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int	ft_strinput(char *str)
{
	char	*error_msg;

	error_msg = "(null)";
	if (!str)
	{
		ft_putstr_fd(error_msg, 1);
		return (ft_strlen(error_msg));
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}
