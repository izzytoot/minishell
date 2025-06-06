/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array_w_null.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:14:47 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/04 14:32:56 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_array_w_null(char **array, int n)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (n-- > 0)
	{
		if (array[i])
			array[i] = safe_free(array[i]);
		i++;
	}
	array = safe_free(array);
	return ;
}
