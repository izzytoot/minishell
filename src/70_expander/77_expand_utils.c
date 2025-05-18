/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   77_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/18 18:33:19 by ddo-carm         ###   ########.fr       */
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
			count++;
		i++;
	}
	return (count);
}

char	**copy_array(int size, char **array)
{
	char	**new_array;
	int		n;
	int		i;

	new_array = ft_calloc(size + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	n = -1;
	i = -1;
	while (n < size - 1)
	{
		if (array[++i])
		{
			new_array[++n] = ft_strdup(array[i]);
			if (!new_array[n])
			{
				ft_free_arrays((void **)new_array);
				return (NULL);
			}
		}
	}
	new_array[size] = NULL;
	return (new_array);
}
