#include "../include/minishell.h"

char	**copy_env(char **env)
{
	char	**env_copy;
	int		var;

	int var = 0;
	while (env[var])
		var++;
	env_copy = (char **)malloc((var + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	var = 0;
	while (env[var])
	{
		env_copy[var] = ft_strdup(env[var]);
		var++;
	}
	env_copy[var] = NULL;
	return (env_copy);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	shell.env = copy_env(envp);
}