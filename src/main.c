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

	input = readline("minishell$ ");
	if (!input)
		return (0);
	//lexer(input);

	return (0);
}