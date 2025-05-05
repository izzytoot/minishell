/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   61_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/02 17:24:38 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_pipe(t_msh **msh, t_tree_nd *node)
{
	int	fd[2]; // fd[0]: read process, fd[1]: write process
	pid_t	left_pid;
	pid_t	right_pid;
	int 	status;
	
	status = 0;
	if (safe_pipe(msh, fd) < 0)
		return (exit_value(msh, 32, 1, 0)) ; //broken pipe is 32?
	left_pid = safe_fork(msh);
	if (left_pid == 0) //child process (left)
	{
		perf_left_pipe(msh, fd[0], fd[1], left_pid);
		status = exec_tree(msh, node->left); //executes left
		exit (status); // was exit(EXIT_SUCCESS)
	}
	right_pid = safe_fork(msh);
	if (right_pid == 0) //child process (right)
	{
		perf_right_pipe(msh, fd[1], fd[0], right_pid);
		status = exec_tree(msh, node->right);
		exit (status); // was exit(EXIT_SUCCESS)
	}
	close_fd(fd[0], fd[1]);
	status = safe_waitpid(left_pid, right_pid);
	return (exit_value(msh, status, 1, 0)); //added
}

void	perf_left_pipe(t_msh **msh, int useless_fd, int dup_fd, int curr_pid)
{
	close(useless_fd); // close read
	safe_dup2(msh, dup_fd, STDOUT_FILENO, curr_pid); // stdout will write to the pipe instead of the terminal. It replaces the terminal with fd[1] (pipe).
	close(dup_fd); // original fd[1] is no longer needed
	return ;
}

void	perf_right_pipe(t_msh **msh, int useless_fd, int dup_fd, int curr_pid)
{
	close(useless_fd); // close write
	safe_dup2(msh, dup_fd, STDIN_FILENO, curr_pid); // stdin will write to the pipe instead of the terminal. It replaces the terminal with fd[1] (pipe).
	close(dup_fd); // original fd[1] is no longer needed
	return ;
}

int	safe_waitpid(int pid1, int pid2)
{
	int status;

	status = 0;
	if (pid1)
	{
		waitpid(pid1, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	if (pid2)
	{
		waitpid(pid2, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	return (status);
}

void close_fd(int fd_1, int fd_2)
{
	close(fd_1);
	close(fd_2);
}
