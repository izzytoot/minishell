/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   75_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/07 16:04:15 by isabel           ###   ########.fr       */
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

bool	check_mid(char c)
{
	if ((ft_strchr(SYM_EXP, c) || c != '$') && !ft_strchr(QUOTE, c))
		return (true);
	return (false);
}
