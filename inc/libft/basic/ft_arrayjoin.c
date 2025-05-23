/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:29:55 by isabel            #+#    #+#             */
/*   Updated: 2025/05/24 00:37:50 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	array_len(char **array)
{
	int i;
	
	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

char	**ft_array_join(char **arr1, char **arr2) 
{
	int len1;
	int len2;
	char **final_arr;
	int j;
	
	len1 = array_len(arr1);
	len2 = array_len(arr2);
	j = 0;
	int i = 0;
	final_arr = malloc((len1 + len2 + 1) * sizeof(char *));
	if (!final_arr)
		return NULL;
	while (i < len1) 
	{
		final_arr[i] = arr1[i];
		i++;
	}
	while (j < len2)
	{
		final_arr[i + j] = arr2[j];
		j++;
	}
	final_arr[len1 + len2] = NULL;
	return (final_arr);
}
