/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:06:13 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/02 15:12:53 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	case_error(char *msg, int code)
{
	int	err;

	err = errno;
	if (err != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		errno = err;
		perror(msg);
		errno = 0;
	}	
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(msg, 2);
	}
	return (code);
}

void	exit_with_error(char *arg, int code)
{
	int	err;

	err = errno;
	ft_putstr_fd("minishell: ", 2);
	errno = err;
	perror(arg);
	errno = 0;
	exit(code);
}

void	exit_with_status(int status)
{
	exit(status);
}
