/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:40:49 by root              #+#    #+#             */
/*   Updated: 2025/04/30 10:40:00 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_arrays(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		safe_free(array[i++]);
	safe_free(array);
	return ;
}
