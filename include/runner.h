#ifndef RUNNER_H
# define RUNNER_H

# include "minishell.h"

int	ft_strcmp(char *s1, char *s2);

int	execute_cmd(t_cmd *cmd);
int	is_builtin(char *cmd);
int	execute_builtin(char **cmd_arg);

int	builtin_echo();
int	builtin_cd();
int	builtin_pwd();
int	builtin_export();
int	builtin_unset();
int	builtin_env();
int	builtin_exit();

#endif