/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/03 19:56:29 by icunha-t         ###   ########.fr       */
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
		create_child_process(&(*msh), cmd_node);
}

void	create_child_process(t_minishell **msh, t_tree_node *node)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed"); //change accordingly
		return ;
	}
	if (pid == 0) // not parent
	{
		if(node->type == ENV_CMD)
			exec_env_cmd(&(*msh), node);
		exit(0); // to correct
	}
	else
		waitpid(pid, &status, 0); //wait for child
}

void	exec_env_cmd(t_minishell **msh, t_tree_node *node)
{
	char 	**envp;
	char 	**av;
	
	if (!node || !node->cmd)
	{
		ft_putstr_fd(ERR_CNOTFOUND, STDERR_FILENO);
		exit (127); //check
	}
	av = node->args;
	envp = (*msh)->envp;
	execve(node->cmd, av, envp);
	free(envp);
	exit(1);
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