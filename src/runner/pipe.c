#include "../../include/minishell.h"

// typedef struct	s_fds
// {
// 	int	infd;
// 	int	outfd;
// 	int	pipefd[2];
// }	t_fds;

static void	child_left(int *pfd, t_ast *root, t_shell *shell)
{
	close(pfd[0]);
	if (dup2(pfd[1], 1) == -1)
		exit_with_error(); //close second fd
	close(pfd[1]);
	exit(runner(root->left, shell));
}

static void	child_right(int *pfd, t_ast *root, t_shell *shell)
{
	close(pfd[1]);
	if (dup2(pfd[0], 0) == -1)
		exit_with_error(); //close second fd
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
		return (case_error("Fork", 1));
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
		return (case_error("Pipe", 1));
	pid1 = fork();
	if (pid1 == -1)
	{
		close(pfd[1]);
		close(pfd[0]);
		return (case_error("Fork", 1));
	}
	if (pid1 == 0)
		child_left(pfd, root, shell);
	return(parent_process(pfd, pid1, root, shell));
}
