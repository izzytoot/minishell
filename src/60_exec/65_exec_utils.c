/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   65_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:19:13 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/16 17:24:17 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("msh: fork: "); // check pre-error message
		if (pid == 0) //if in child
			exit (EXIT_FAILURE);
		return(-1);
	}
	return (pid);	
}

int safe_dup(int old_fd, int curr_pid)
{
	int	new_fd;
	
	new_fd = dup(old_fd); //returns a duplicate of old_fd
	if (new_fd < 0)
	{
		perror("msh: dup: "); // msh: dup: Bad file descriptor
		close(new_fd);
		if (curr_pid == 0)
			exit (EXIT_FAILURE);
		return (-1);
	}
	return (new_fd);
}

/*
closes dest_fd
duplicates src_fd to dest_fd - dest_fd is now src_fd
*/
void safe_dup2(int src_fd, int dest_fd, int curr_pid)
{
	if (dup2(src_fd, dest_fd) < 0)
	{
		perror("msh: dup2: ");
		close(src_fd);
		if (curr_pid == 0)
			exit (EXIT_FAILURE);
		return ;
	}
	close(src_fd);
	return ;
}

int	safe_pipe(int pipe_fd[2])
{
	int pid;

	pid = getpid();
	if (pipe(pipe_fd) < 0) // anything writen to fd[1] can be read from fd[0].
	{
		perror("msh: pipe: "); // check pre-error message
		if (pid == 0) 
			exit(EXIT_FAILURE);
		return(-1);
	}
	return(0);
}
