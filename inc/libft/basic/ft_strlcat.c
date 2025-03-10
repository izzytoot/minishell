/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:58:52 by icunha-t          #+#    #+#             */
/*   Updated: 2024/12/18 13:54:21 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dst_len;
	unsigned int	src_len;

	dst_len = 0;
	src_len = 0;
	while (dst[dst_len])
		dst_len++;
	while (src[src_len])
		src_len++;
	if (size <= dst_len)
		return (size + src_len);
	i = dst_len;
	j = 0;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}
