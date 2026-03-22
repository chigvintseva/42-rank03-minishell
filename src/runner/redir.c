/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:28:18 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/22 14:56:29 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_input(t_redir *redirs)
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
	char	*line;
	int		pfd[2];

	if (pipe(pfd) == -1)
		return (case_error("Pipe", 1));
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			close(pfd[1]);
			close(pfd[0]);
			return (case_error("Readline", 1));
		}
		if (!ft_strcmp(redirs->target, line))
		{
			free(line);
			break ;
		}
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], "\n", 1);
		free(line);
	}
	close(pfd[1]);
	if (dup2(pfd[0], 0) == -1)
	{
		close(pfd[0]);
		return (case_error("Dup2", 1));
	}
	close(pfd[0]);
	return (0);
}

int	apply_redirs(t_redir *redirs)
{
	
	if (!redirs)
		return (0);
	if (redirs->type == R_IN)
		return (redir_input(redirs));
	if (redirs->type == R_OUT)
		return (redir_output(redirs));
	if (redirs->type == R_APPEND)
		return (redir_append(redirs));
	if (redirs->type == R_HEREDOC)
		return (redir_heredoc(redirs));
	return (-1);
}
