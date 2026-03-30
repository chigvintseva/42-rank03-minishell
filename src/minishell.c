/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:17:08 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/28 23:00:58 by aleksandra       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	input_precheck(char *input)
{
	int	ret;

	ret = check_specialchars(input);
	if (ret == 1)
		return (case_error("minishell: Invalid character", EXIT_FAILURE));
	if (ret == 2)
		return (case_error("minishell:  unexpected EOF while looking for matching `\"'", 2));
	return (EXIT_SUCCESS);
}

// int	gen_file_open(t_shell *shell, char *hd_path)
// {
// 	char	*hd_id;
// 	int		fd;

// 	while (1)
// 	{
// 		hd_id = ft_itoa(shell->heredoc_id++);
// 		if (!hd_id)
// 			return (case_error("ft_itoa", 1));
// 		hd_path = ft_strjoin("/tmp/minishell_hd_", hd_id);
// 		free(hd_id);
// 		if (!hd_path)
// 			return (case_error("ft_strjoin", 1));
// 		fd = open(hd_path, O_CREAT | O_EXCL | O_WRONLY, 0600);
// 		if (fd == -1 && errno == EEXIST)
// 		{
// 			free(hd_path);
// 			continue ;
// 		}
// 		if (fd == -1)
// 			return (free(hd_path), case_error("Open", 1));
// 		break ;
// 	}
// 	return (fd);
// }

static int	read_heredoc(t_redir *redirs, t_shell *shell)
{
	char	*line;
	int		fd;
	char	*hd_id;
	char	*hd_path;

	while (1)
	{
		hd_id = ft_itoa(shell->heredoc_id++);
		if (!hd_id)
			return (case_error("ft_itoa", 1));
		hd_path = ft_strjoin("/tmp/minishell_hd_", hd_id);
		free(hd_id);
		if (!hd_path)
			return (case_error("ft_strjoin", 1));
		fd = open(hd_path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd == -1 && errno == EEXIST)
		{
			free(hd_path);
			continue ;
		}
		if (fd == -1)
			return (free(hd_path), case_error("Open", 1));
		break ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			return (case_error("minishell: warning: here-document at line 133 delimited by end-of-file", 1));
		}
		if (!ft_strcmp(redirs->target, line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(redirs->target);
	redirs->target = ft_strdup(hd_path);
	if (!redirs->target)
		return (free(hd_path), case_error("ft_strdup", 1));
	free(hd_path);
	return (0);
}

static int	prepare_heredocs_ast(t_ast *root, t_shell *shell)
{
	t_redir	*redir;
	int		status;

	if (!root || !shell)
		return (0);
	status = 0;
	if (root->type == AST_CMD && root->cmd)
	{
		redir = root->cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				status = read_heredoc(redir, shell);
				if (status != 0)
					return (status);
			}
			redir = redir->next;
		}
	}
	else if (root->type == AST_PIPE)
	{
		status = prepare_heredocs_ast(root->left, shell);
		if (status != 0)
			return (status);
		status = prepare_heredocs_ast(root->right, shell);
		if (status != 0)
			return (status);
	}
	return (0);
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
	tokens = lexer(input, shell);
	if (!tokens)
		return (case_error("minishell: lexer error", 1));
	root = parse_tokens(tokens);
	if (!root)
		return (free_tokens(tokens), case_error("minishell: syntax error near unexpected token", 1));
	status = prepare_heredocs_ast(root, shell);
	if (status != 0)
	{
		free_tokens(tokens);
		free_ast(root);
		return (status);
	} 
	status = runner(root, shell);
	free_tokens(tokens);
	free_ast(root);
	return (status);
}
