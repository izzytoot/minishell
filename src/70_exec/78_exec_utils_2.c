/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   78_exec_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:42:59 by isabel            #+#    #+#             */
/*   Updated: 2025/06/04 15:20:36 by icunha-t         ###   ########.fr       */
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

bool	ch_if_sub_cmd(t_tree_nd *node)
{
	if (node->cmd || !node->args[0])
		return (false);
	if ((ft_strcmp(node->args[0], ".") == 0)
		|| (ft_strcmp(node->args[0], "..") == 0))
		return (false);
	if (node->quote_lst->in_quotes)
		return (false);
	if (!node->cmd && node->args[0])
		return (true);
	return (false);
}

int	output_cmd_errors(t_msh **msh, t_tree_nd *node)
{
	if (node->type == ARG && !node->args[0])
		return (exit_value(msh, 0, 1, 0));
	else if (node->type == ARG && (ft_strcmp(".", node->args[0]) == 0))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_PT);
		return (exit_value(msh, 2, 1, 0));
	}
	ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
	return (exit_value(msh, 127, 1, 0));
}
