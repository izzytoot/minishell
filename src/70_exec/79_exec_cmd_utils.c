/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   79_exec_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:54:29 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/07 16:46:14 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	deal_with_cmd(t_msh **msh, t_tree_nd *node, int *status)
{
	if (ch_if_sub_cmd(msh, node))
		sub_cmd(msh, node, &node->args);
	*status = exec_cmd(msh, node);
}

int	exec_cmd_child(t_msh **msh, t_tree_nd *node, int *status)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, sig_c_child);
	if (node->type == ENV_CMD)
	{
		if (node->cmd_content)
			ft_free_arrays((void **)node->cmd_content);
		node->cmd_content = join_cmd_and_args((node->cmd), node->args);
		*status = exec_env_cmd(&(*msh), node);
		return (exit_value(msh, *status, 1, 1));
	}
	return (output_cmd_errors(msh, node));
}

void	exec_cmd_parent(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	wait(&(*status));
	waitpid(pid, &(*status), 0);
	signal(SIGINT, sig_c_main);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = 128 + WTERMSIG(*status);
	if (*status == 131)
		ft_printf("Quit (core dumped)\n");
}
