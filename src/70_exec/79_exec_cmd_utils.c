/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   79_exec_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:54:29 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/09 20:02:07 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	deal_with_cmd(t_msh **msh, t_tree_nd *node, int *status)
{
	if (ch_if_sub_cmd(msh, node))
		sub_cmd(msh, node, &node->args);
	*status = exec_cmd(msh, node);
}

void	exec_cmd_parent(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	wait(&status);
	waitpid(pid, &status, 0);
	signal(SIGINT, sig_c_main);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		status = 128 + WTERMSIG(status);
	}
	if (status == 131)
		ft_printf("Quit (core dumped)\n");
}
