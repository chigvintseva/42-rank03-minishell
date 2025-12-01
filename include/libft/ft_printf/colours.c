/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:15:28 by achigvin          #+#    #+#             */
/*   Updated: 2025/09/11 16:34:38 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

void	red(char style)
{
	if (style == 0)
		ft_printf("\e[0;31m");
	else if (style == 'b')
		ft_printf("\e[1;31m");
	else if (style == 'i')
		ft_printf("\e[3;31m");
}

void	green(char style)
{
	if (style == 0)
		ft_printf("\e[0;32m");
	else if (style == 'b')
		ft_printf("\e[1;32m");
	else if (style == 'i')
		ft_printf("\e[3;32m");
}

void	yellow(char style)
{
	if (style == 0)
		ft_printf("\e[0;93m");
	else if (style == 'b')
		ft_printf("\e[1;93m");
	else if (style == 'i')
		ft_printf("\e[3;93m");
}
