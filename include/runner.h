#ifndef RUNNER_H
# define RUNNER_H

# include "minishell.h"
# include <sys/wait.h>


typedef struct s_shell
{
	char	**env;
	int		exit_status;
}	t_shell;

int		ft_strcmp(char *s1, char *s2);
void	free_matrix(char **matrix);
char	*free_return(char **to_free, char *to_return);

int		execute_cmd(t_cmd *cmd, t_shell	*shell);
char	*parsing(char *cmd, char **envp, int *perm_error);

int		builtin_echo();
int		builtin_cd();
int		builtin_pwd();
int		builtin_export();
int		builtin_unset();
int		builtin_env();
int		builtin_exit();

#endif