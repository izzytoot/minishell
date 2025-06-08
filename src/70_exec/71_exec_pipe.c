/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/08 11:56:45 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_pipe(t_msh **msh, t_tree_nd *node)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;
	int		fd[2];

	status = 0;
	if (safe_pipe(msh, fd) < 0)
		return (exit_value(msh, 141, 1, 0));
	left_pid = safe_fork(msh);
	if (left_pid == 0)
	{
		perf_left_pipe(msh, fd[0], fd[1]);
		status = exec_tree(msh, node->left);
		exit_value(msh, status, 1, 1);
	}
	right_pid = safe_fork(msh);
	if (right_pid == 0)
	{
		perf_right_pipe(msh, fd[1], fd[0]);
		status = exec_tree(msh, node->right);
		exit_value(msh, status, 1, 1);
	}
	close_fd(fd[0], fd[1]);
	status = safe_waitpid(left_pid, right_pid);
	return (exit_value(msh, status, 1, 0));
}

void	perf_left_pipe(t_msh **msh, int useless_fd, int dup_fd)
{
	close(useless_fd);
	safe_dup2(msh, dup_fd, STDOUT_FILENO);
	close(dup_fd);
	return ;
}

void	perf_right_pipe(t_msh **msh, int useless_fd, int dup_fd)
{
	close(useless_fd);
	safe_dup2(msh, dup_fd, STDIN_FILENO);
	close(dup_fd);
	return ;
}

int	safe_waitpid(int pid1, int pid2)
{
	int	status;

	status = 0;
	if (pid1)
	{
		wait(&status);
		waitpid(pid1, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	if (pid2)
	{
		wait(&status);
		waitpid(pid2, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	return (status);
}

void	close_fd(int fd_1, int fd_2)
{
	close(fd_1);
	close(fd_2);
}
