/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   61_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/01 18:46:54 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_pipe(t_msh **msh, t_tree_nd *node)
{
	int	fd[2]; // fd[0]: read process, fd[1]: write process
	pid_t	left_pid;
	pid_t	right_pid;
	int 	status;
	
	if(safe_pipe(fd) < 0)
		return ;
	left_pid = safe_fork();
	if (left_pid == 0) //child process (left)
	{
		perform_left_pipe(fd[0], fd[1], left_pid);
		exec_tree(msh, node->left); //executes left
		exit_value(msh, status, 1, 1);
	//	exit (EXIT_SUCCESS) ;
	}
	right_pid = safe_fork();
	if (right_pid == 0) //child process (right)
	{
		perform_right_pipe(fd[1], fd[0], right_pid);
		exec_tree(msh, node->right);
		exit_value(msh, status, 1, 1);
	//	exit (EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
}

void	perform_left_pipe(int useless_fd, int dup_fd, int curr_pid)
{
	close(useless_fd); // close read
	safe_dup2(dup_fd, STDOUT_FILENO, curr_pid); // stdout will write to the pipe instead of the terminal. It replaces the terminal with fd[1] (pipe).
	close(dup_fd); // original fd[1] is no longer needed
}

void	perform_right_pipe(int useless_fd, int dup_fd, int curr_pid)
{
	close(useless_fd); // close write
	safe_dup2(dup_fd, STDIN_FILENO, curr_pid); // stdin will write to the pipe instead of the terminal. It replaces the terminal with fd[1] (pipe).
	close(dup_fd); // original fd[1] is no longer needed
}
