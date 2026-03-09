#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline

void	print_tokens(t_token *lst)
{
	while (lst)
	{
		printf("type: %d valuse: %s\n", lst->type, lst->value);
		lst = lst->next;
	}	
}

void	exit_with_error(char *msg, int code)
{
	if (errno)
		perror(msg);
	else
		printf("%s\n", msg);
	exit(code);
}

int	main(int argc, char *argv[])
{
	char	*input;
	int		error;
	t_token	*tokens;

	input = readline("minishell$ ");
	if (!input)
		return (0);
	error = check_specialchars(input);
	if (error == 1)
		return (free(input), exit_with_error("Invalid character", 1), 1);
	if (error == 2)
		return (free(input), exit_with_error("Unclosed quotes", 1), 1);
	tokens = lexer(input);
	if (!tokens)
		return (free(input), exit_with_error("Error", 1), 1);
	print_tokens(tokens);
	free_tokens(tokens);
	free(input);
	return (0);
}
