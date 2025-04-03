/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/03 18:48:07 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
iterar tokens todos
verificar se primeiro is builtin ou env cmd
se for ver qual is e exec
*/

#include "../../inc/minishell.h"

void	exec_single_cmd(t_minishell **msh)
{
	t_tree_node	*cmd_node;
	
	cmd_node = (*msh)->tree_root;
	if (cmd_node->type == BT_CMD)
	{
		if (ft_strcmp(cmd_node->cmd, "echo") == 0)
			ft_echo(&(*msh));
		else if (ft_strcmp(cmd_node->cmd, "cd") == 0)
			ft_cd(&(*msh));
		else if (ft_strcmp(cmd_node->cmd, "pwd") == 0)
			print_work_dir();
		//else if (cmd_node->cmd =="export")
		//	ft_export(&(*msh));
		//else if (cmd_node->cmd == "unset")
		//	ft_unset(&(*msh));
		else if (ft_strcmp(cmd_node->cmd, "env") == 0)
			print_env(&(*msh));
		//else if (cmd_node->cmd =="exit")
		//	ft_exit(&(*msh));
	}
	else
	{
		
	}
	
	//if ENV - fork and execve
}
/*
void	exec_tree(t_minishell **msh)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		
	}
	if ((*msh)->tree_root->type == PIPE)
	{
		
	}
}
	*/