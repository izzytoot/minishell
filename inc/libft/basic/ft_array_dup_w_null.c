/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup_w_null.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:46:06 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/21 17:19:27 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_non_null_entries(char **array, int n);

//divided the function in 2

char	**ft_array_dup_w_null(char **array, int n)
{
	int		i;
	int		size;
	char	**new_array;

	if (!array)
		return (NULL);
	size = ft_count_non_null_entries(array, n);
	new_array = malloc(sizeof(char *) * (size + 1));
	if (!new_array)
		return (NULL);
	i = -1;
	n = -1;
	while (n < size - 1)
	{
		if (array[++i])
		{
			new_array[++n] = ft_strdup(array[i]);
			if (!new_array[n])
				return (ft_free_arrays((void **)new_array), NULL);
		}
	}
	new_array[size] = NULL;
	return (new_array);
}

static int	ft_count_non_null_entries(char **array, int n)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (n-- >= 0)
	{
		if (array[++i])
			count++;
	}
	return (count);
}
