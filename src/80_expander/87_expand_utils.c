/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   87_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/07 00:07:02 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	recurs_exp_args(t_msh **msh, t_tree_nd *node)
{
	if (node->left)
		expand_args(msh, node->left);
	if (node->right)
		expand_args(msh, node->right);
}

int	get_kw_len(char *arg, int **i, int tmp_i, bool *flag)
{
	int	len;

	len = 0;
	while (!ft_strchr(WS, arg[(**i)++]))
	{
		if (arg[tmp_i + 1] == '?')
		{
			(**i)++;
			*flag = true;
			return (1);
		}
		if (arg[**i] == '$' || ft_strchr(SYM_EXP, arg[**i]))
			break ;
		len++;
	}
	return (len);
}

bool	check_mid(char c)
{
	if ((ft_strchr(SYM_EXP, c) || c != '$') && c != '\"')
		return (true);
	return (false);
}

int	count_exp(char *arg, int i)
{
	int	count;

	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] != '$')
				i++;
			count++;
		}
		if (arg[i])
			i++;
	}
	return (count);
}
