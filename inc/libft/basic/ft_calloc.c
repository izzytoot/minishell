/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:13:34 by icunha-t          #+#    #+#             */
/*   Updated: 2024/11/22 15:12:52 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dest;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, nmemb * size);
	return ((void *)dest);
}
