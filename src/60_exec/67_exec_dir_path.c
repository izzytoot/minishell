/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   67_exec_dir_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:42:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/18 18:10:54 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	choose_path(t_msh **msh, t_tree_nd *node, char **path)
{
	int	status;

	if (!path)
		*path = NULL;
	status = 0;
	//if (node->cmd && (((node->cmd[0] == '.' && node->cmd[1] == '/')
	//			|| node->cmd[0] == '/')))
	if (ft_strchr(node->cmd, '/') || (!node->cmd
			&& ft_strchr(node->args[0], '/'))) //changed to any cmd containing /
	{
		if (!node->cmd)
			*path = node->args[0];
		else
			*path = node->cmd;
		status = direct_path(node);
		exit_value(msh, status, 1, 0);
	}
	else
		*path = check_env_cmd(node->cmd, get_path((*msh)->envp_list), -1);
	return (status);
}

int	direct_path(t_tree_nd *node)
{
	char	*path;
	int		status;

	status = 0;
	if (!node->cmd)
		path = node->args[0]; //for case of calling exp dir like $PATH or $HOME
	else
		path = node->cmd; //removed ptr of path
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
