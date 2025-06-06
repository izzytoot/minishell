/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   88_expand_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:06:38 by isabel            #+#    #+#             */
/*   Updated: 2025/06/07 00:07:29 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
			array[i] = safe_free(array[i]);
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

char	**ft_array_dup_null(t_tree_nd *node, char **array, int n)
{
	int		i;
	int		size;
	char	**new_array;

	if (!array)
		return (NULL);
	size = 0;
	i = 0;
	while (n-- > 0)
	{
		if (array[i])
			size++;
		i++;
	}
	node->nb_arg = size;
	new_array = copy_array(size, array);
	return (new_array);
}
