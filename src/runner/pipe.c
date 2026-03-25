/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:57:30 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/25 17:35:29 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_left(int *pfd, t_ast *root, t_shell *shell)
{
	close(pfd[0]);
	if (dup2(pfd[1], 1) == -1)
		exit_with_error();
	close(pfd[1]);
	exit(runner(root->left, shell));
}

static void	child_right(int *pfd, t_ast *root, t_shell *shell)
{
	close(pfd[1]);
	if (dup2(pfd[0], 0) == -1)
		exit_with_error();
	close(pfd[0]);
	exit(runner(root->right, shell));
}

static int	parent_process(int *pfd, pid_t pid1, t_ast *root, t_shell *shell)
{
	int		status1;
	int		status2;
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		close(pfd[1]);
		close(pfd[0]);
		return (case_error("Fork", EXIT_FAILURE));
	}
	if (pid2 == 0)
		child_right(pfd, root, shell);
	close(pfd[1]);
	close(pfd[0]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	if (WIFSIGNALED(status2))
		return (128 + WTERMSIG(status2));
	return (-1);
}

int	run_pipe(t_ast *root, t_shell *shell)
{
	int		pfd[2];
	pid_t	pid1;

	if (pipe(pfd) == -1)
		return (case_error("Pipe", EXIT_FAILURE));
	pid1 = fork();
	if (pid1 == -1)
	{
		close(pfd[1]);
		close(pfd[0]);
		return (case_error("Fork", EXIT_FAILURE));
	}
	if (pid1 == 0)
		child_left(pfd, root, shell);
	return(parent_process(pfd, pid1, root, shell));
}
