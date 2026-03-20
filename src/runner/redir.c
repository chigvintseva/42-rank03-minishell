#include "../../include/minishell.h"

static int	redir_input(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_RDONLY);
	if (fd == -1)
		return (perror("open"), 1); // ??
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (perror("dup2"), 1); // ??
	}
	close(fd);
	return (0);
}

static int	redir_output(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), 1); // ??
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (perror("dup2"), 1); // ??
	}
	close(fd);
	return (0);
}

static int	redir_append(t_redir *redirs)
{
	int	fd;

	fd = open(redirs->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), 1); // ??
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (perror("dup2"), 1); // ??
	}
	close(fd);
	return (0);
}

static int	redir_heredoc(t_redir *redirs)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) == -1)
		exit_with_error("pipe", EXIT_FAILURE); // ??
	while (1)
	{
		line = readline("heredoc> ", EXIT_FAILURE);
		if (!line)
		{
			close(pfd[1]);
			close(pfd[0]);
			return (perror("readline"), 1); // ??
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
		return (perror("dup2"), 1); // ??
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
	return (0);
}
