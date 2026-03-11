#include "../../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(char **cmd_arg)
{
	if (!ft_strcmp(cmd_arg[0], "echo"))
		return (builtin_echo());
	if (!ft_strcmp(cmd_arg[0], "cd"))
		return (builtin_cd());
	if (!ft_strcmp(cmd_arg[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd_arg[0], "export"))
		return (builtin_export());
	if (!ft_strcmp(cmd_arg[0], "unset"))
		return (builtin_unset());
	if (!ft_strcmp(cmd_arg[0], "env"))
		return (builtin_env());
	if (!ft_strcmp(cmd_arg[0], "exit"))
		return (builtin_exit());
	return (0);
}

int	execute_external(t_cmd *cmd)
{
	
}

int	execute_cmd(t_cmd *cmd) // argv = {{ls} {-l}}
{
	if (!cmd || !cmd->argv)
		return (0);
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(cmd->argv));
	return (execute_external(cmd));
}