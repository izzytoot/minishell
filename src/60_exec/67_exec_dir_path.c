/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   67_exec_dir_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:42:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/13 13:05:00 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	choose_path(t_msh **msh, t_tree_nd *node, char **path)
{
	int	status;

	if (!path)
		*path = NULL;
	//if (node->cmd && (((node->cmd[0] == '.' && node->cmd[1] == '/')
	//			|| node->cmd[0] == '/')))
	if (ft_strchr(node->cmd, '/')) //changed to any cmd containing /
	{
		*path = node->cmd;
		status = direct_path(&(*msh), node);
		exit_value(msh, status, 1, 0);
	}
	else
		*path = check_env_cmd(node->cmd, get_path((*msh)->envp_list), -1);
	return (status);
}

int	direct_path(t_msh **msh, t_tree_nd *node)
{
	char	*path;
	int		status;

	(void)msh;
	status = 0;
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
