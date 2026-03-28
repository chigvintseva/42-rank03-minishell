/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:28:18 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/27 18:03:06 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_input(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_RDONLY);
	if (fd == -1)
		return (case_error("Open", 1)); // print error: "minishell: <redirs->target>: No such file or directory"
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (case_error("Dup2", 1));
	}
	close(fd);
	return (0);
}

static int	redir_output(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (case_error("Open", 1));
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (case_error("Dup2", 1));
	}
	close(fd);
	return (0);
}

static int	redir_append(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (case_error("Open", 1));
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (case_error("Dup2", 1));
	}
	close(fd);
	return (0);
}

static int	redir_heredoc(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_RDONLY);
	if (fd == -1)
		return (case_error("Open", 1));
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (case_error("Dup2", 1));
	}
	close(fd);
	unlink(redirs->target);
	return (0);
}

int	apply_redirs(t_redir *redirs)
{
	int	result;

	while (redirs)
	{
		if (redirs->type == R_IN)
			result = redir_input(redirs);
		else if (redirs->type == R_OUT)
			result = redir_output(redirs);
		else if (redirs->type == R_APPEND)
			result = redir_append(redirs);
		else if (redirs->type == R_HEREDOC)
			result = redir_heredoc(redirs);
		if (result != 0)
			return (result);
		redirs = redirs->next;
	}
	return (0);
}
