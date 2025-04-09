/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:19:13 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/09 18:03:33 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("msh: fork");  // Parent: return error code; Child: exit to prevent code execution.
		if (getpid() != getppid()) //if in child
			exit (EXIT_FAILURE);
		return(-1);
	}
	return (pid);	
}

int safe_dup(int old_fd, int curr_pid)
{
	int	new_fd;
	
	new_fd = dup(old_fd);
	if (new_fd < 0)
	{
		perror("msh: dup");
		close(new_fd);
		if (curr_pid == 0)
			exit (EXIT_FAILURE);
		return (-1);
	}
	return (new_fd);
}

void safe_dup2(int new_fd, int old_fd, int curr_pid)
{
	if (dup2(new_fd, old_fd) < 0) // new_fd is duplicated form old_fd
	{
		perror("msh: dup2"); // check error
		close(new_fd);
		if (curr_pid == 0) //if in child
			exit (EXIT_FAILURE);
		return ;
	}
	close(new_fd);
	return ;
}
