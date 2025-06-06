/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   75_remake_args_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:14:35 by isabel            #+#    #+#             */
/*   Updated: 2025/06/06 15:53:36 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_aux_structs(t_flag_str *flags, t_ints *ints, t_tree_nd *node)
{
	(*flags).written = false;
	(*flags).space_prev = true;
	(*flags).space_next = node->quote_lst->sp_case;
	(*ints).i = 0;
	(*ints).j = 0;
}

void	compose_arg(t_ints *ints, t_flag_str *flags, char **new_args,
			t_tree_nd *node)
{
	if ((*ints).j == 0 || (((*flags).space_next || (*flags).space_prev)
			&& node->args[(*ints).i + 1]))
	{
		new_args[(*ints).j] = ft_strjoin(node->args[(*ints).i],
				node->args[(*ints).i + 1]);
		(*ints).i++;
		if (node->quote_lst->next)
			node->quote_lst = node->quote_lst->next;
	}
	else
	{
		if (!(*flags).space_next && !(*flags).space_prev)
		{
			(*ints).j--;
			new_args[(*ints).j] = ft_strjoin(new_args[(*ints).j],
					node->args[(*ints).i]);
		}
		else
			new_args[(*ints).j] = ft_strdup(node->args[(*ints).i]);
	}
	(*flags).written = true;
	(*flags).space_prev = false;
	(*ints).j++;
}

void	add_last(t_ints *ints, t_flag_str *flags, char **new_args,
			t_tree_nd *node)
{
	(*ints).j--;
	new_args[(*ints).j] = ft_strjoin(new_args[(*ints).j],
			node->args[(*ints).i]);
	(*flags).written = true;
	(*flags).space_prev = true;
	(*ints).j++;
}

void	lonely_arg(t_ints *ints, t_flag_str *flags, char **new_args,
			t_tree_nd **node)
{
	new_args[(*ints).j] = ft_strdup((*node)->args[(*ints).i]);
	(*ints).j++;
	(*ints).i++;
	if ((*node)->quote_lst->next)
		(*node)->quote_lst = (*node)->quote_lst->next;
	(*flags).written = false;
	(*flags).space_prev = true;
}

void	handle_written(t_ints *ints, t_flag_str *flags, t_tree_nd **node)
{
	(*ints).i++;
	if (!(*node)->quote_lst->sp_case)
		(*flags).space_next = false;
	else
	{
		(*flags).space_next = true;
		(*flags).space_prev = true;
	}
	if ((*node)->quote_lst->next)
		(*node)->quote_lst = (*node)->quote_lst->next;
	(*flags).written = false;
}
