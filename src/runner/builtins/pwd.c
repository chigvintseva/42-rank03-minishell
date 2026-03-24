/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:06 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/24 17:40:58 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	const *find_pwd_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (envp[i] + 4);
		i++;
	}
	return (NULL);
}

int	builtin_pwd(char **argv, char **env)
{
	char const	*pwd;

	if (argv[1])
		return(case_error("pwd: too many arguments", 1)); // or without msg
	pwd = find_pwd_env(env);
	if (pwd)
	{
		printf("%s\n", pwd);
		return (EXIT_SUCCESS);
	}
	return (1);
}
