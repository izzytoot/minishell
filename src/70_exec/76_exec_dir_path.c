/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   76_exec_dir_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:42:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/09 20:07:00 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	choose_path(t_msh **msh, t_tree_nd *node, char **path)
{
	char	*env_path;
	char	*cwd;

	*path = NULL;
	if (is_direct_command(node))
		return (handle_direct_command(msh, node, path));
	if (node->cmd && ft_strcmp(node->cmd, "minishell") == 0)
	{
		cwd = safe_getcwd(*msh, true);
		if (!cwd)
			return (exit_value(msh, 1, 1, 0));
		*path = ft_strjoin(cwd, "/minishell");
		free(cwd);
		if (!*path)
			return (exit_value(msh, 1, 1, 0));
		return (exit_value(msh, direct_path(node), 1, 0));
	}
	env_path = get_path((*msh)->envp_list);
	*path = check_env_cmd(node->cmd, env_path, -1, 2);
	if (!(*path))
		handle_no_path(msh, node);
	return (0);
}

int	direct_path(t_tree_nd *node)
{
	char	*path;
	int		status;

	status = 0;
	if (!node->cmd)
		path = node->args[0];
	else
		path = node->cmd;
	if (access(path, F_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: No such file or directory\n", path);
		status = 127;
	}
	else if (ft_is_dir(path))
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: Is a directory\n", path);
		status = 126;
	}
	else if (access(path, X_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: Permission denied\n", path);
		status = 126;
	}
	return (status);
}

int	is_direct_command(t_tree_nd *node)
{
	if (node->cmd && ft_strchr(node->cmd, '/'))
		return (1);
	if (!node->cmd && node->args[0] && ft_strchr(node->args[0], '/'))
		return (1);
	return (0);
}

int	handle_direct_command(t_msh **msh, t_tree_nd *node, char **path)
{
	int	status;

	if (!node->cmd)
		*path = node->args[0];
	else
		*path = node->cmd;
	status = direct_path(node);
	return (exit_value(msh, status, 1, 0));
}

int	handle_no_path(t_msh **msh, t_tree_nd *node)
{
	if (!node->args[0])
		return (exit_value(msh, 0, 1, 1));
	ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
	return (exit_value(msh, 127, 1, 1));
}
