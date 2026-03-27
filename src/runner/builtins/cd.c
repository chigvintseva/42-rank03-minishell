/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:55:11 by aleksandra        #+#    #+#             */
/*   Updated: 2026/03/27 17:38:37 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	cd_error(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
}

static int	invalid_args(char **argv)
{
	if (!ft_strcmp(argv[1], "~") ||  !ft_strcmp(argv[1], "-") )
		return (cd_error(argv[1]), case_error("Not supported argument", EXIT_FAILURE));
	if (argv[2])
		return (case_error("minishell: cd: too many arguments", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **argv)
{
	char	*path;
	char	*cur_dir;
	
	if (!argv[1])
	{
		return(EXIT_SUCCESS);
		//return (TO THE HOME DIR);
	}
	if (!ft_strcmp(argv[1], "."))
		return (EXIT_SUCCESS);
	if (invalid_args(argv))
		return (EXIT_FAILURE);
	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (case_error("getcwd failed", EXIT_FAILURE));
	path = argv[1];
	if (chdir((const char *)path) != 0)
		return (free(cur_dir), cd_error(argv[1]), case_error("", EXIT_FAILURE));
	// change env var
	free(cur_dir);
	return (EXIT_SUCCESS);
}
