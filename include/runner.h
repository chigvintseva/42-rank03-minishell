#ifndef RUNNER_H
# define RUNNER_H

# include "minishell.h"
# include <sys/wait.h>
# include <fcntl.h>


typedef struct s_shell
{
	char	**env;
	int		exit_status;
	int		run_further;
}	t_shell;

typedef struct	s_fds
{
	int	infd;
	int	outfd;
	int	pipefd[2];
}	t_fds;

int		ft_strcmp(char *s1, char *s2);
void	free_matrix(char **matrix);
char	*free_return(char **to_free, char *to_return);

int		run_cmd(t_cmd *cmd, t_shell	*shell);
char	*parsing(char *cmd, char **envp, int *perm_error);
int		apply_redirs(t_redir *redirs);

int		builtin_echo();
int		builtin_cd();
int		builtin_pwd();
int		builtin_export();
int		builtin_unset();
int		builtin_env();
int		builtin_exit();

#endif