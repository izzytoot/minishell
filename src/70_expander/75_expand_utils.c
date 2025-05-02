/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   75_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/02 11:44:43 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	recurs_exp_tree(t_msh **msh, t_tree_nd *node)
{
	if (node->left)
		expand_tree(msh, node->left);
	if(node->right)
		expand_tree(msh, node->right);
}

int	get_kw_len(char *arg, int **i, int tmp_i, bool *flag)
{
	int	len;

	len = 0;
	while(!ft_strchr(WHITESPACE, arg[(**i)++]))
	{
		if (arg[tmp_i + 1] == '?')
		{
			(**i)++;
			*flag = true;
			return (1);
		}
		if(arg[**i] == '$' || ft_strchr(SYM_EXP, arg[**i]))
			break;
		len++;
	}
	return (len);
}
