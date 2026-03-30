/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:19:26 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/25 18:07:04 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include <sys/wait.h>
# include <fcntl.h>

int		run_cmd_node(t_ast *node, t_shell *shell);
int		run_pipe_node(t_ast *root, t_shell *shell);
int		runner(t_ast *node, t_shell *shell);
int		run_pipe(t_ast *root, t_shell *shell);

int		run_cmd(t_cmd *cmd, t_shell	*shell);
char	*parsing(char *cmd, char **envp, int *perm_error);
void	free_matrix(char **matrix);
int		apply_redirs(t_redir *redirs);

int		is_builtin(char *cmd);
int		execute_builtin(char **cmd_argv, t_shell *shell);
int		run_builtin(t_cmd *cmd, t_shell *shell);

char 	*get_env_var(char **env, const char *key);
void 	update_env(char **env, const char *key, const char *value);

int		builtin_echo(char **argv);
int		builtin_cd(char **argv, char **env);
int		builtin_pwd(void);

//export
size_t	key_len(char *arg);
int		has_equal(char *arg);
int		is_valid_identifier(char *arg);
size_t	find_env_key(char **env, char *arg);
int		export_error(char *arg);
size_t	env_len(char **env);
char	**dup_env(char **env);
char	**sort_env(char **copy);
void	sorted_print(char **sorted);
int		builtin_export(char **agrv, t_shell *shell);

int		builtin_unset(char **argv, char ***env);
int		builtin_env(char **envp, char **argv);
int		builtin_exit(char **argv, t_shell *shell);

#endif