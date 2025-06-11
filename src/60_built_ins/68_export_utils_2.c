/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   68_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:49:51 by isabel            #+#    #+#             */
/*   Updated: 2025/06/11 17:31:27 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_export_util(t_msh **msh, bool s_qt, char *arg, char	**var_inf)
{
	t_list	*current;
	bool	fl;

	fl = false;
	if (!s_qt && sing_exp(arg))
	{
		current = (*msh)->envp_list;
		while (current)
		{
			if (ft_strncmp(current->content, arg, ft_strlen(arg)) == 0)
			{
				fl = true;
				break ;
			}
			current = current->next;
		}
		if (!fl)
			add_only_to_export(*msh, arg);
	}
	else
		add_export_var(&(*msh)->envp_list, var_inf[0], var_inf[1]);
}

void	get_var_info(t_tree_nd **node, t_quote *tmp_lst, int i, char ***var_inf)
{
	char	*s_qt_info;

	if (((*node)->args && (*node)->args[i]) && (tmp_lst->next
			&& tmp_lst->next->in_squotes))
	{
		s_qt_info = ft_strjoin((*node)->args[i], (*node)->args[i + 1]);
		*var_inf = ft_split(s_qt_info, '=');
		s_qt_info = safe_free(s_qt_info);
	}
	else
		*var_inf = ft_split((*node)->args[i], '=');
}

void	move_on(int *i, t_quote **tmp_lst)
{
	(*i)++;
	*tmp_lst = (*tmp_lst)->next;
	if (*tmp_lst && (*tmp_lst)->in_squotes)
	{
		(*i)++;
		*tmp_lst = (*tmp_lst)->next;
	}
}
