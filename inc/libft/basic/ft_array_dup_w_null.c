/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup_w_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:46:06 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/09 13:32:05 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_array_dup_w_null(char **array, int n)
{
	int		i;
	int		size;
	char	**new_array;

	if (!array)
		return (NULL);
	size = 0;
	i = -1;
	while (n-- >= 0)
	{
		if (array[++i])
			size++;
	}
	new_array = malloc(sizeof(char *) * (size + 1));
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
