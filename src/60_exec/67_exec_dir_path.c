/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   67_exec_dir_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:42:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/12 18:08:26 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*choose_path(t_msh **msh, t_tree_nd *node)
{
	char *path;

	if (node->args[0] && ((node->args[0][0] == '.' && node->args[0][1] == '/')
		|| node->args[0][0] == '/'))
	{
		path = node->args[0];
		direct_path(&(*msh), node);
	}
	else
		path = check_env_cmd(node->cmd, get_path((*msh)->envp_list), -1);
	return (path);
}


int	direct_path(t_msh **msh, t_tree_nd *node)
{
	char	*path;
	int		status;

	status = 0;
	path = node->args[0];
	if (access(path, F_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: No such file or directory\n", path);
		status = 127;
	}
	if (ft_is_dir(path))
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: Is a directory\n", path);
		status = 126;
	}
	if (access(path, X_OK) != 0)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: Permission denied\n", path);
		status = 126;
	}
	update_shlvl(&(*msh)->envp_list);
	return (exit_value(msh, status, 1, 0));
}
