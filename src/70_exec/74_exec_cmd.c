/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   74_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/12 11:55:26 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_msh **msh, t_tree_nd *node)
{
	int		status;
	int		pid;

	status = 0;
	pid = 0;
	if (node->type == BT_CMD)
	{
		status = exec_bt_cmd(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	}
	pid = safe_fork(msh);
	if (pid == 0)
	{
		sig_cmd_child();
		exec_cmd_child(msh, node, &status);
		return (exit_value(msh, status, 1, 1));
	}
	else
	{
		if (exec_sh_v(&(*msh), node) == 0)
			status = exit_value(msh, 0, 1, 0);
		exec_cmd_parent(pid, &status);
	}
	return (exit_value(msh, status, 1, 0));
}

int	exec_bt_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	if (ft_strcmp(node->cmd, "echo") == 0)
		status = ft_echo(&node);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		status = ft_cd(msh, &node);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(node->cmd, "export") == 0)
		status = ft_export(msh, &node, 0, 0);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		status = ft_unset(msh, &node);
	else if (ft_strcmp(node->cmd, "env") == 0)
		status = print_env(msh, &node);
	else if (ft_strcmp(node->cmd, "exit") == 0)
		status = ft_exit(msh, &node);
	else if (ft_strcmp(node->cmd, "''") == 0)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s", node->cmd, ERR_CNOTFOUND);
		status = 127;
	}
	return (exit_value(msh, status, 1, 0));
}

int	exec_env_cmd(t_msh **msh, t_tree_nd *node)
{
	char	*path;
	int		status;

	status = choose_path(&(*msh), node, &path);
	if (status != 0)
		return (exit_value(msh, status, 1, 0));
	if (safe_execve(msh, path, node->cmd_content))
		return (exit_value(msh, status, 1, 1));
	return (exit_value(msh, status, 1, 1));
}

int	exec_sh_v(t_msh **msh, t_tree_nd *node)
{
	int		status;
	int		i;
	char	**split;

	status = 0;
	i = -1;
	if (node->args)
	{
		while (node->args[++i])
		{
			if (check_shell_var(node->args[i]))
			{
				split = ft_split(node->args[i], '=');
				if (!split || !split[0])
					return (ft_free_arrays((void *)split), EXIT_FAILURE);
				if (update_var(&(*msh)->vars_list, split[0], split[1])
					!= EXIT_SUCCESS)
					return (ft_free_arrays((void *)split), EXIT_FAILURE);
				ft_free_arrays((void *)split);
			}
		}
	}
	if (!(*msh)->vars_list)
		return (-1);
	return (exit_value(msh, status, 1, 0));
}

int	safe_execve(t_msh **msh, char *path, char **argv)
{
	char	**envp_array;

	envp_array = cpy_for_execve(&(*msh));
	if (!envp_array)
		return (EXIT_FAILURE);
	if (execve(path, argv, envp_array) == -1)
	{
		perror("msh: execve:");
		ft_free_arrays((void **)envp_array);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
