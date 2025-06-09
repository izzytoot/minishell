/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   78_exec_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:42:59 by isabel            #+#    #+#             */
/*   Updated: 2025/06/09 20:06:56 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	arg_expansions(t_tree_nd *node)
{
	t_quote	*curr_qt;

	curr_qt = node->quote_lst;
	while (curr_qt)
	{
		if (curr_qt->exp)
			return (true);
		curr_qt = curr_qt->next;
	}
	return (false);
}

bool	ch_if_sub_cmd(t_msh **msh, t_tree_nd *node)
{
	char	*tmp_cmd;

	tmp_cmd = NULL;
	if (node->cmd)
		tmp_cmd = ft_strdup(node->cmd);
	if ((tmp_cmd && !ch_shlvl_bin(msh, tmp_cmd)) || (!node->args
			|| !node->args[0]))
	{
		tmp_cmd = safe_free(tmp_cmd);
		return (false);
	}
	if ((ft_strcmp(node->args[0], ".") == 0)
		|| (ft_strcmp(node->args[0], "..") == 0) || node->quote_lst->in_quotes)
	{
		tmp_cmd = safe_free(tmp_cmd);
		return (false);
	}
	if ((!node->cmd || ch_shlvl_bin(msh, tmp_cmd)) && node->args[0])
	{
		tmp_cmd = safe_free(tmp_cmd);
		return (true);
	}
	return (false);
}

int	output_cmd_errors(t_msh **msh, t_tree_nd *node)
{
	if (node->type == ARG && !node->args[0])
		return (exit_value(msh, 0, 1, 1));
	else if (node->type == ARG && (ft_strcmp(".", node->args[0]) == 0))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_PT);
		return (exit_value(msh, 2, 1, 1));
	}
	else if (get_path((*msh)->envp_list) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s", node->args[0],
			ERR_DIRNOTFOUND);
		return (exit_value(msh, 127, 1, 1));
	}
	ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
	return (exit_value(msh, 127, 1, 1));
}

char	**get_joinned_array(char *tmp_cmd, char **sep_args_tmp,
	char ****new_args)
{
	char		**joinned_array;

	joinned_array = NULL;
	if (tmp_cmd)
		joinned_array = ft_array_join((ft_array_dup(sep_args_tmp)),
				(ft_array_dup((**new_args) + 1)));
	else
		joinned_array = ft_array_join((ft_array_dup(sep_args_tmp + 1)),
				(ft_array_dup((**new_args) + 1)));
	return (joinned_array);
}
