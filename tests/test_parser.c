/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:00:00 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/09 12:00:00 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

// Helper functions for creating tokens (since lexer.c is missing)
t_token	*create_token(const char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	free_tokens(t_token *lst)
{
	t_token	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp->value);
		free(temp);
	}
}

// Function to print the AST
void	print_ast(t_ast *node, int depth)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (node->type == AST_CMD)
	{
		printf("CMD: ");
		if (node->cmd && node->cmd->argv)
		{
			for (int j = 0; j < node->cmd->argc; j++)
			{
				if (j > 0)
					printf(" ");
				printf("%s", node->cmd->argv[j]);
			}
		}
		if (node->cmd && node->cmd->redirs)
		{
			t_redir *redir = node->cmd->redirs;
			while (redir)
			{
				printf(" ");
				if (redir->type == R_IN)
					printf("< %s", redir->target);
				else if (redir->type == R_OUT)
					printf("> %s", redir->target);
				else if (redir->type == R_APPEND)
					printf(">> %s", redir->target);
				else if (redir->type == R_HEREDOC)
					printf("<< %s", redir->target);
				redir = redir->next;
			}
		}
		printf("\n");
	}
	else if (node->type == AST_PIPE)
	{
		printf("PIPE\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
}

// Function to create tokens from a string (simple implementation)
t_token	*create_tokens_from_string(char *str)
{
	t_token	*head = NULL;
	char	*token_str;
	int		i = 0;

	while (str[i])
	{
		// Skip spaces
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;

		if (!str[i])
			break;

		// Check for operators
		if (str[i] == '|')
		{
			tokenadd_back(&head, create_token("|", PIPE));
			i++;
		}
		else if (str[i] == '<')
		{
			if (str[i+1] == '<')
			{
				tokenadd_back(&head, create_token("<<", HEREDOC));
				i += 2;
			}
			else
			{
				tokenadd_back(&head, create_token("<", REDIR_IN));
				i++;
			}
		}
		else if (str[i] == '>')
		{
			if (str[i+1] == '>')
			{
				tokenadd_back(&head, create_token(">>", REDIR_APPEND));
				i += 2;
			}
			else
			{
				tokenadd_back(&head, create_token(">", REDIR_OUT));
				i++;
			}
		}
		else
		{
			// Word token
			int start = i;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|' && str[i] != '<' && str[i] != '>')
				i++;
			token_str = ft_substr(str, start, i - start);
			tokenadd_back(&head, create_token(token_str, WORD));
			free(token_str);
		}
	}
	return (head);
}

int	main(int argc, char **argv)
{
	t_ast	*ast;
	t_token	*tokens;
	char	*input;

	if (argc < 2)
	{
		printf("Usage: %s \"command to parse\"\n", argv[0]);
		return (1);
	}
	input = argv[1];
	printf("Parsing command: %s\n", input);

	// For now, we'll manually create tokens since lexer is not implemented
	// This is a simplified tokenization for testing
	tokens = create_tokens_from_string(input);
	if (!tokens)
	{
		printf("Failed to create tokens\n");
		return (1);
	}

	ast = parse_tokens(tokens);
	if (!ast)
	{
		printf("Failed to parse tokens\n");
		free_tokens(tokens);
		return (1);
	}

	printf("Parsed AST:\n");
	print_ast(ast, 0);

	free_ast(ast);
	free_tokens(tokens);
	printf("Parsing completed successfully!\n");
	return (0);
}