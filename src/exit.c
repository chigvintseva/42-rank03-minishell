/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:43:36 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/16 15:25:36 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_with_error(char *msg, int code)
{
	if (errno)
		perror(msg);
	else
		printf("Error: %s\n", msg);
	exit(code);
}
