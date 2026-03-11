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

int	main(int argc, char *argv[])
{
	char	*input;
	t_token	*tokens;

	input = readline("minishell$ ");
	if (!input)
		return (0);
	tokens = lexer(input);
	print_tokens(tokens);
	free_tokens(tokens);
	free(input);
	return (0);
}
