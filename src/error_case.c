/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:06:13 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/01 19:31:23 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	case_error(char *msg, int code)
{
	if (errno != 0)
	{
		//code = errno;
		perror(msg);
	}	
	else
		ft_putendl_fd(msg, 2);
	return (code);
}

void	exit_with_error(char *arg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	perror(arg);
	//exit(errno);
	exit(code);
}

void	exit_with_status(int status)
{
	exit(status);
}
