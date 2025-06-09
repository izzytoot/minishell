/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/09 20:30:21 by ddo-carm         ###   ########.fr       */
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
		get_msh(*msh, 0);
		signal(SIGINT, ctrl_c_hd);
		signal(SIGPIPE, sig_ig);
		perf_left_pipe(msh, fd[0], fd[1]);
		status = exec_tree(msh, node->left);
		exit_value(msh, status, 1, 1);
	}
	right_pid = safe_fork(msh);
	if (right_pid == 0)
		pipe_right_child(msh, node, &status, fd);
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
		signal(SIGINT, SIG_IGN);
		waitpid(pid1, &status, 0);
		signal (SIGINT, sig_c_main);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			status = 130;
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			status = 130;
			write(1, "\n", 1);
		}
		else if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 0;
	}
	if (pid2)
		status = pid2_handler(pid2, status);
	return (status);
}

void	close_fd(int fd_1, int fd_2)
{
	close(fd_1);
	close(fd_2);
}
