/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:17:08 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/21 18:11:49 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	input_precheck(char *input)
{
	int	ret;

	ret = check_specialchars(input);
	if (ret == 1)
		return (case_error("Invalid character", 1));
	if (ret == 2)
		return (case_error("Unclosed quotation", 1));
	return (0);
}


static void	print_redirs(t_redir *redirs, int depth)
{
	int		i;
	t_redir	*current;

	if (!redirs)
		return ;
	current = redirs;
	while (current)
	{
		i = 0;
		while (i < depth + 4)
		{
			ft_putchar_fd(' ', 1);
			i++;
		}
		if (current->type == R_IN)
			ft_putstr_fd("Redir: < ", 1);
		else if (current->type == R_OUT)
			ft_putstr_fd("Redir: > ", 1);
		else if (current->type == R_APPEND)
			ft_putstr_fd("Redir: >> ", 1);
		else if (current->type == R_HEREDOC)
			ft_putstr_fd("Redir: << ", 1);
		ft_putendl_fd(current->target, 1);
		current = current->next;
	}
}

static void	print_std_helper(t_ast *ast, int depth)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	while (i < depth)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (ast->type == AST_PIPE)
	{
		ft_putendl_fd("PIPE", 1);
		if (ast->left)
			print_std_helper(ast->left, depth + 2);
		if (ast->right)
			print_std_helper(ast->right, depth + 2);
	}
	else if (ast->type == AST_CMD && ast->cmd)
	{
		ft_putstr_fd("CMD: ", 1);
		if (ast->cmd->argc > 0 && ast->cmd->argv)
			ft_putendl_fd(ast->cmd->argv[0], 1);
		else
			ft_putendl_fd("[empty]", 1);
		if (ast->cmd->argc > 1 && ast->cmd->argv)
		{
			i = 0;
			while (i < depth + 2)
			{
				ft_putchar_fd(' ', 1);
				i++;
			}
			ft_putstr_fd("Args: ", 1);
			i = 1;
			while (i < ast->cmd->argc)
			{
				ft_putstr_fd(ast->cmd->argv[i], 1);
				if (i < ast->cmd->argc - 1)
					ft_putstr_fd(", ", 1);
				i++;
			}
			ft_putchar_fd('\n', 1);
		}
		if (ast->cmd->redirs)
			print_redirs(ast->cmd->redirs, depth);
	}
}

static void	print_std(t_ast *ast)
{
	if (!ast)
	{
		ft_putendl_fd("[NULL AST]", 1);
		return ;
	}
	ft_putendl_fd("=== AST STRUCTURE ===", 1);
	print_std_helper(ast, 0);
	ft_putendl_fd("=== END AST ===", 1);
}

int	minishell(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_ast	*root;
	int		status;

	status = input_precheck(input);
	if (status != 0)
		return (status);
	errno = 0;
	tokens = lexer(input);
	if (!tokens)
		return (case_error("Lexer error", 1));
	root = parse_tokens(tokens);
	print_std(root);
	if (!root)
		return (free_tokens(tokens), case_error("Parser error", 1));
	status = runner(root, shell);
	free_tokens(tokens);
	free_ast(root);
	return (status);
}
