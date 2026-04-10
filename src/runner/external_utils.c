/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:10:39 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/10 17:11:40 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_matrix(char **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	check_is_dir(char *cmd_path)
{
	struct stat	st;

	if (stat(cmd_path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_path, 2);
			ft_putendl_fd(": Is a directory", 2);
			exit(126);
		}
	}
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	cmd_no_permission(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	exit(126);
}
