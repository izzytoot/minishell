/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/06 18:03:46 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_sh_v(t_msh **msh, t_tree_nd *node);

int	exec_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;
	
	status = 0;
	if (node->type == BT_CMD)
	{
		status = exec_bt_cmd(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	}
	else if (node->type == ENV_CMD)
	{
		node->cmd_content = join_cmd_and_args(node->cmd, node->args);
		status = exec_env_cmd(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	} 
	else if (node->type == SH_V)
	{
		status = exec_sh_v(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
		return (exit_value(msh, 127, 1, 0));
	}
}

int	exec_sh_v(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	ft_lstnew((*msh)->vars_list);
	if (!(*msh)->vars_list)
		return (EXIT_FAILURE);
	while (node->cmd && node->type == SH_V)
	{
		(*msh)->vars_list->content = node->cmd;
		node->cmd = node->right->cmd;
		(*msh)->vars_list = (*msh)->vars_list->next;
	}
	return (exit_value(msh, status, 1, 0));
}

int	exec_bt_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	if (ft_strcmp(node->cmd, "echo") == 0)
		status = ft_echo(&node); //returns exit code
	else if (ft_strcmp(node->cmd, "cd") == 0)
		status = ft_cd(msh, &node);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(node->cmd, "export") == 0)
		status = ft_export(msh, &node);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		status = ft_unset(msh, &node);
	else if (ft_strcmp(node->cmd, "env") == 0)
		status = print_env(msh, &node);
	else if (ft_strcmp(node->cmd, "exit") == 0)
		ft_exit(msh, &node); // tem que ser transformado em int
	return (exit_value(msh, status, 1, 0));
}

int	exec_env_cmd(t_msh **msh, t_tree_nd *node)
{
	pid_t	pid;
	char	*path;
	int		status;
	
	pid = safe_fork(msh);
	status = 0;
	if (pid == 0)
	{
		////se path comeca com ./, isso é o path
		path = check_env_cmd(node->cmd, get_path((*msh)->envp_list), -1);
		if (execve(path, node->cmd_content, (*msh)->envp) == -1)
			perror("msh: execve: "); // check pre-error message
	}
	else
	{
		waitpid(pid, &status, 0); //wait for exit code from child
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	return (exit_value(msh, status, 1, 0));
}
