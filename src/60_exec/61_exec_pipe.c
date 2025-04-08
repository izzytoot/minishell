/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   61_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/08 19:24:25 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_pipe(t_minishell **msh, t_tree_node *node)
{
	int	fd[2]; // fd[0]: read process, fd[1]: write process
	pid_t	left_pid;
	pid_t	right_pid;
	int status;

	pipe(fd); // anything written to fd[1] can be read from fd[0].
	left_pid = my_fork();
	if (left_pid == 0) //child process (left)
		perform_left_pipe(msh, node, fd[0], fd[1]);
	right_pid = my_fork();
	if (right_pid == 0) //child process (right)
		perform_right_pipe(msh, node, fd[1], fd[0]);
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
}

void	perform_left_pipe(t_minishell **msh, t_tree_node *node, int useless_fd, int dup_fd)
{
	close(useless_fd); // close read
	dup2(dup_fd, STDOUT_FILENO); // stdout will write to the pipe instead of the terminal. It replaces the terminal with fd[1] (pipe).
	close(dup_fd); // original fd[1] is no longer needed
	exec_tree(msh, node->left); //executes left
	exit(0);
}

void	perform_right_pipe(t_minishell **msh, t_tree_node *node, int useless_fd, int dup_fd)
{
	close(useless_fd); // close read
	dup2(dup_fd, STDIN_FILENO); // stdout will write to the pipe instead of the terminal. It replaces the terminal with fd[1] (pipe).
	close(dup_fd); // original fd[1] is no longer needed
	exec_tree(msh, node->right); //executes left
	exit(0);
}
