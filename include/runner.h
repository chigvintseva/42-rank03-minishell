/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:19:26 by achigvin          #+#    #+#             */
/*   Updated: 2026/03/20 16:19:26 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

int	run_cmd_node(t_ast *node, t_shell *shell);
int	run_pipe_node(t_ast *root, t_shell *shell);
int	runner(t_ast *node, t_shell *shell);

#endif