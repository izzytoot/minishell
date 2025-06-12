/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   79_exec_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:54:29 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/12 11:56:52 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	deal_with_cmd(t_msh **msh, t_tree_nd *node, int *status)
{
	if (ch_if_sub_cmd(msh, node))
		sub_cmd(msh, node, &node->args);
	*status = exec_cmd(msh, node);
}

void	exec_cmd_child(t_msh **msh, t_tree_nd *node, int *status)
{
	if (node->type == ENV_CMD)
	{
		if (node->cmd_content)
			ft_free_arrays((void **)node->cmd_content);
		node->cmd_content = join_cmd_and_args((node->cmd), node->args);
		*status = exec_env_cmd(&(*msh), node);
	}
	else if (exec_sh_v(msh, node) == 0)
		return ;
	else
		*status = output_cmd_errors(msh, node);
}

void	exec_cmd_parent(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &(*status), 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		*status = 130;
		write(1, "\n", 1);
	}
	else if (*status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	else if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else
		*status = 0;
}
