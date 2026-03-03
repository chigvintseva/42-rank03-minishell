//#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline


int is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		return (0);
	lexer(input);
	//printf("%s\n", input);

	// int len;
	// count_len(input, &len);
	// printf("%d\n", len);
	return (0);
}