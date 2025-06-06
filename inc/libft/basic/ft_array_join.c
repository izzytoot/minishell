/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:29:55 by isabel            #+#    #+#             */
/*   Updated: 2025/06/06 15:42:56 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

char	**ft_array_join(char **arr1, char **arr2)
{
	int		len1;
	int		len2;
	char	**final_arr;
	int		j;
	int		i;

	len1 = array_len(arr1);
	len2 = array_len(arr2);
	j = 0;
	i = -1;
	final_arr = malloc((len1 + len2 + 1) * sizeof(char *));
	if (!final_arr)
		return (NULL);
	while (++i < len1)
		final_arr[i] = arr1[i];
	while (j < len2)
	{
		final_arr[i + j] = arr2[j];
		j++;
	}
	final_arr[len1 + len2] = NULL;
	arr1 = safe_free(arr1);
	arr2 = safe_free(arr2);
	return (final_arr);
}
