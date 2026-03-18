#include "../../include/minishell.h"

void	apply_redirs(t_redir *redirs)
{
	int fd;

	if (redirs->type == R_IN)
	{
		fd = open(redirs->target, O_RDONLY);
        if (fd == -1)
                perror(redirs->target);
		if (dup2(fd, 0) == -1)
                exit_with_error("dup2", EXIT_FAILURE); // ??
		close(fd);
	}
	if (redirs->type == R_OUT)
	{
		fd = open(redirs->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1)
                perror(redirs->target);
		if (dup2(fd, 1) == -1)
                exit_with_error("dup2", EXIT_FAILURE); // ??
		close(fd);
	}
	if (redirs->type == R_APPEND)
	{
		fd = open(redirs->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd == -1)
                perror(redirs->target);
		if (dup2(fd, 1) == -1)
                exit_with_error("dup2", EXIT_FAILURE); // ??
		close(fd);
	}
	if (redirs->type == R_HEREDOC)
		return (R_HEREDOC);
}
