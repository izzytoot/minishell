/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   79_1_exec_pipe_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:56:28 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/09 20:28:58 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_right_child(t_msh **msh, t_tree_nd *node, int *status, int *fd)
{
	get_msh(*msh, 0);
	signal(SIGINT, ctrl_c_hd);
	signal(SIGPIPE, sig_ig);
	perf_right_pipe(msh, fd[1], fd[0]);
	*status = exec_tree(msh, node->right);
	exit_value(msh, *status, 1, 1);
}

int	pid2_handler(int pid2, int status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid2, &status, 0);
	signal (SIGINT, sig_c_main);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (130);
	else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		return (130);
		write(1, "\n", 1);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}
