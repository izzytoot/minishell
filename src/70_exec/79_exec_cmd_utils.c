/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   79_exec_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:54:29 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/09 15:12:41 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	deal_with_cmd(t_msh **msh, t_tree_nd *node, int *status)
{
	if (ch_if_sub_cmd(msh, node))
		sub_cmd(msh, node, &node->args);
	*status = exec_cmd(msh, node);
}

// int	exec_cmd_child(t_msh **msh, t_tree_nd *node, int *status)
// {
// 	int	pid;

// 	pid = safe_fork(msh);
// 	if (pid == 0)
// 	{
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGINT, sig_c_child);
// 		if (node->type == ENV_CMD)
// 		{
// 			if (node->cmd_content)
// 				ft_free_arrays((void **)node->cmd_content);
// 			node->cmd_content = join_cmd_and_args((node->cmd), node->args);
// 			*status = exec_env_cmd(&(*msh), node);
// 			return (exit_value(msh, *status, 1, 1));
// 		}
// 	}
// 	exec_cmd_parent(pid, status);
// 	//return (exit_value(msh, *status, 1, 1));
// 	return (exit_value(msh, *status, 1, 0));
// }

void	exec_cmd_parent(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	wait(&status);
	waitpid(pid, &status, 0); //here
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
