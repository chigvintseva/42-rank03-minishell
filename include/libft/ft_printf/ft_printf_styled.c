/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_styled.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:12:32 by achigvin          #+#    #+#             */
/*   Updated: 2025/09/11 16:18:33 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

void	reset(char style)
{
	if (style == 0)
		ft_printf("\e[0;0m");
	else if (style == 'b')
		ft_printf("\e[1;0m");
	else if (style == 'i')
		ft_printf("\e[3;0m");
}

void	ft_printf_styled(char *str, char colour, char style)
{
	if (colour == 'r')
		red(style);
	else if (colour == 'g')
		green(style);
	else if (colour == 'y')
		yellow(style);
	else if (style == 'w')
		reset(style);
	ft_printf(str);
	reset(0);
}
