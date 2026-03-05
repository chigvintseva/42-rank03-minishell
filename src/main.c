#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h> //cc main.c -lreadline

void handle_quotes(char quote, int *len, char **word, char *s, int *i)
{
		(*i)++;
		while (s[*i] && s[*i] != quote)
		{
			if(word)
				*(*word)++ = s[(*i)++];
			else
			{
				(*len)++;
				(*i)++;
			}
		}
		if (s[*i] != quote)
			; // return error
		(*i)++;
}

void	count_len(t_lexer *input, int *len)
{
	int	tmp_i;

	*len = 0;
	tmp_i = input->i;
	while (!is_operator(input->s[tmp_i]) && !is_space(input->s[tmp_i]) && input->s[tmp_i])
	{
		if (input->s[tmp_i] != '"' && input->s[tmp_i] != '\'')
		{
			(*len)++;
			tmp_i++;
		}
		if (input->s[tmp_i] == '"')
			handle_quotes('"', len, 0, input->s, &tmp_i); //NULL
		if (input->s[tmp_i] == '\'')
			handle_quotes('\'', len, 0, input->s, &tmp_i); //NULL
	}
}

void	handle_word(t_lexer *input)
{
	char	*word;
	int		len;
	char	*tmp;

	count_len(input, &len); // check error		
	word = malloc((len * sizeof(char)) + 1);
	if (!word)
		return ;
	tmp = word;
	while (!is_operator(input->s[input->i]) && !is_space(input->s[input->i])
		&& input->s[input->i])
	{
		if (input->s[input->i] != '"' && input->s[input->i] != '\'')
			*word++ = input->s[input->i++];
		if (input->s[input->i] == '"')
			handle_quotes('"', 0, &word, input->s, &input->i);
		if (input->s[input->i] == '\'')
			handle_quotes('\'', 0, &word, input->s, &input->i);
	}
	*word = '\0';
	//create token
	printf("%s\n", tmp);
	free(tmp);
}

int	main(int argc, char *argv[])
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		return (0);
	//lexer(input);

	t_lexer	lex;
	lex.s = input;
	lex.i = 0;
	handle_word(&lex);

	return (0);
}