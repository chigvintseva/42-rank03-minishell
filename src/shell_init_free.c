/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:59:53 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/26 22:41:14 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	free_env_copy(char **env_copy, size_t cnt)
{
	size_t	i;

	i = 0;
	while (i < cnt)
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
}

void	free_shell(t_shell *shell)
{
	size_t	i;

	if (!shell->env)
	{
		rl_clear_history();
		return ;
	}
	i = 0;
	while (shell->env[i] != NULL)
	{
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
	rl_clear_history();
}

int init_shell(t_shell *shell, char **envp)
{
	char	**envp_copy;
	size_t	i;
	
	shell->env = NULL;
	shell->exit_status = 0;
	shell->run_further = 1;
	shell->heredoc_id = 0;
	i = 0;
	while (envp[i] != NULL)
		i++;
	envp_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_copy)
		return (1);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
			return (free_env_copy(envp_copy, i), 1);
		i++;
	}
	envp_copy[i] = NULL;
	shell->env = envp_copy;
	return (0);
}
