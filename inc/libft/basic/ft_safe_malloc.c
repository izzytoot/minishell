/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:16:31 by isabel            #+#    #+#             */
/*   Updated: 2025/05/10 20:39:43 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*safe_malloc(size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if (!res)
		return (NULL);
	return (res);
}
