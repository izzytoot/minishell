/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   66_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:19:13 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/10 20:01:30 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	safe_fork(t_msh **msh)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("msh: fork: "); // check pre-error message
		if (pid == 0) //if in child
			exit_value(msh, 1, 1, 1);
		return(-1);
	}
	return (pid);	
}

int safe_dup(t_msh **msh, int old_fd, int curr_pid)
{
	int	new_fd;
	
	new_fd = dup(old_fd); //returns a duplicate of old_fd
	if (new_fd < 0)
	{
		perror("msh: dup: "); // msh: dup: Bad file descriptor
		close(new_fd);
		if (curr_pid == 0)
			exit_value(msh, 1, 1, 1);
		return (-1);
	}
	return (new_fd);
}

/*
closes dest_fd
duplicates src_fd to dest_fd - dest_fd is now src_fd
*/
void safe_dup2(t_msh **msh, int src_fd, int dest_fd, int curr_pid)
{
	if (dup2(src_fd, dest_fd) < 0)
	{
		perror("msh: dup2: ");
		close(src_fd);
		if (curr_pid == 0)
			exit_value(msh, 1, 1, 1);
	}
	close(src_fd);
}

int	safe_pipe(t_msh **msh, int pipe_fd[2])
{
	int pid;

	pid = getpid();
	if (pipe(pipe_fd) < 0) // anything writen to fd[1] can be read from fd[0].
	{
		perror("msh: pipe: "); // check pre-error message
		if (pid == 0)
			exit_value(msh, 1, 1, 1);
		return(-1);
	}
	return(0);
}
void	update_shlvl(t_list **env_list)
{
	char    *shlvl_value;
	char    *shlvl_str;
    int     shlvl;
	
	shlvl_value = get_var_val(*env_list, "SHLVL");
	if (shlvl_value)
    {
		shlvl = ft_atoi(shlvl_value);
        shlvl++;
		shlvl_str = ft_itoa(shlvl);
		if (!shlvl_str)
			return ;
		update_var(env_list, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
	else
		update_var(env_list, "SHLVL", "1");
}
