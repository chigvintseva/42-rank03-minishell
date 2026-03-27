/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:06 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/25 17:52:01 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (case_error("pwd", 1));
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
