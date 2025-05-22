/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:17:11 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/22 12:27:17 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_array_dup(char **array)
{
	int		i;
	int		size;
	char	**new_array;

	if (!array)
		return (NULL);
	size = 0;
	while (array[size])
		size++;
	new_array = malloc(sizeof(char *) * (size + 1));
	if (!new_array)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			ft_free_arrays((void **)new_array);
			return (NULL);
		}
	}
	new_array[size] = NULL;
	return (new_array);
}
