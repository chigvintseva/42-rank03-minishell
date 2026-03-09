#include "../include/minishell.h"

int is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_space(const char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	check_specialchars(char *s)
{
	int	i; 
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (s[i] == '"' && !in_single)
			in_double = !in_double;
		else if (!in_single && !in_double)
		{
			if (s[i] == '\\' || s[i] == ';' || s[i] == '(' || s[i] == ')')
				return (1);
			if (s[i] == '&' && s[i + 1] == '&')
				return (1);
		}
		i++;
	}
	if (in_single || in_double)
		return (2);
	return (0);
}
