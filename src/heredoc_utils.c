/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:21:27 by aleksandra        #+#    #+#             */
/*   Updated: 2026/04/03 01:08:35 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_hd_file(t_shell *shell, char **hd_path)
{
	char	*hd_id;
	int		fd;

	while (1)
	{
		hd_id = ft_itoa(shell->heredoc_id++);
		if (!hd_id)
			return (errno = ENOMEM, -1);
		*hd_path = ft_strjoin("/tmp/minishell_hd_", hd_id);
		free(hd_id);
		if (!(*hd_path))
			return (errno = ENOMEM, -1);
		fd = open(*hd_path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd == -1 && errno == EEXIST)
		{
			free(*hd_path);
			continue ;
		}
		if (fd == -1)
			return (free(*hd_path), -1);
		break ;
	}
	return (fd);
}

static int	write_hd_lines(int fd, t_redir *redirs)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			return (0);
		}
		if (!ft_strcmp(redirs->target, line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (1);
}

static int	read_heredoc(t_redir *redirs, t_shell *shell)
{
	int		fd;
	char	*hd_path;

	hd_path = NULL;
	fd = create_hd_file(shell, &hd_path);
	if (fd == -1)
		return (case_error("here-document", EXIT_FAILURE));
	if (!write_hd_lines(fd, redirs))
	{
		errno = 0;
		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(redirs->target, 2);
		ft_putendl_fd("')", 2);
	}
	close(fd);
	free(redirs->target);
	redirs->target = ft_strdup(hd_path);
	if (!redirs->target)
		return (free(hd_path), errno = ENOMEM, case_error("here-document", EXIT_FAILURE));
	free(hd_path);
	return (EXIT_SUCCESS);
}

int	handle_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		status;

	status = 0;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == R_HEREDOC)
		{
			status = read_heredoc(redir, shell);
			if (status != 0)
				return (status);
		}
		redir = redir->next;
	}
	return (status);
}
