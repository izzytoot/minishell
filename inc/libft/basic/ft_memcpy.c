/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:11:58 by icunha-t          #+#    #+#             */
/*   Updated: 2024/12/18 13:53:43 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tempd;
	unsigned const char	*temps;

	i = 0;
	tempd = dest;
	temps = src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		tempd[i] = temps[i];
		i++;
	}
	return (dest);
}
