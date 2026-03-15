#include "../../include/minishell.h"

static char	*find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	exit_with_error("inappropriate environment", EXIT_FAILURE);
	return (NULL);
}

char	*parsing(char *cmd, char **envp, int *perm_error)
{
	char	**envp_path;
	char	*path;
	char	*cmd_path;
	int		i;

	envp_path = ft_split(find_path_env(envp), ':');
	if (!envp_path)
		return (NULL);
	i = 0;
	while (envp_path[i])
	{
		path = ft_strjoin(envp_path[i], "/");
		if (!path)
			return (free_return(envp_path, NULL));
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (!cmd_path)
			return (free_return(envp_path, NULL));
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (free_return(envp_path, cmd_path));
			else
				*perm_error = 1; //means that it is Permission denied
		}
		free(cmd_path);
		i++;
	}
	return (free_return(envp_path, NULL));
}
