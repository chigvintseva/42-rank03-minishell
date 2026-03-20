/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:06:13 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/17 19:02:15 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	case_error(char *msg)
{
	if (errno != 0)
	{
		perror("Error ");
		return (1);
	}	
	else
	{
		ft_putendl_fd(msg, 2);
		return (2);
	}
}
