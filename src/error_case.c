/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:06:13 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/25 19:00:24 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	case_error(char *msg, int code)
{
	if (errno != 0)
	{
		code = errno;
		perror(msg);
	}	
	else
		ft_putendl_fd(msg, 2);
	return (code);
}

void	exit_with_error()
{
	perror("Error");
	exit(errno);
}

void	exit_with_status(int status)
{
	exit(status);
}
