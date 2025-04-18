/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/18 22:26:33 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_cmd(t_minishell **msh, t_tree_node *node)
{
	if (node->type == BT_CMD)
		exec_bt_cmd(&(*msh), node);
	else if (node->type == ENV_CMD)
		exec_env_cmd(&(*msh), node);
	else
	ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
}

void	exec_bt_cmd(t_minishell **msh, t_tree_node *node)
{
	if (ft_strcmp(node->cmd, "echo") == 0)
		ft_echo(&node);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		ft_cd(msh, &node);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		ft_pwd();
	//else if (node->cmd =="export")
	//	ft_export(&(*msh));
	//else if (node->cmd == "unset")
	//	ft_unset(&(*msh));
	else if (ft_strcmp(node->cmd, "env") == 0)
		print_env(msh, &node);
	else if (ft_strcmp(node->cmd, "exit") == 0)
		ft_exit(msh, &node);
}

void	exec_env_cmd(t_minishell **msh, t_tree_node *node)
{
	pid_t	pid;
	char	*path;
	int		status;
	
	pid = safe_fork();
	if (pid == 0)
	{
		path = check_env_cmd(node->cmd, get_path((*msh)->envp_list), -1);
		if (execve(path, node->cmd_content, (*msh)->envp) == -1)
			perror("msh: execve: "); // check pre-error message
	}
	else
		waitpid(pid, &status, 0); //wait for exit code from child
}
