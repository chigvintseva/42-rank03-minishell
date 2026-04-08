/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:28:18 by achigvin          #+#    #+#             */
/*   Updated: 2026/04/07 14:13:42 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_input(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_RDONLY);
	if (fd == -1)
	{
		return (case_error(redirs->target, EXIT_FAILURE));
	}
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (case_error(redirs->target, EXIT_FAILURE));
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	redir_output(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (case_error(redirs->target, EXIT_FAILURE));
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (case_error(redirs->target, EXIT_FAILURE));
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	redir_append(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (case_error(redirs->target, EXIT_FAILURE));
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (case_error(redirs->target, EXIT_FAILURE));
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	redir_heredoc(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_RDONLY);
	if (fd == -1)
		return (case_error(redirs->target, EXIT_FAILURE));
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (case_error(redirs->target, EXIT_FAILURE));
	}
	close(fd);
	unlink(redirs->target);
	return (0);
}

int	apply_redirs(t_redir *redirs)
{
	int	status;

	while (redirs)
	{
		if (redirs->type == R_IN)
			status = redir_input(redirs);
		else if (redirs->type == R_OUT)
			status = redir_output(redirs);
		else if (redirs->type == R_APPEND)
			status = redir_append(redirs);
		else if (redirs->type == R_HEREDOC)
			status = redir_heredoc(redirs);
		if (status != 0)
			return (status);
		redirs = redirs->next;
	}
	return (EXIT_SUCCESS);
}
