/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:36:34 by icunha-t          #+#    #+#             */
/*   Updated: 2024/11/22 15:37:08 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;

	i = 0;
	n_len = ft_strlen(little);
	if (n_len == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& big[i + j] == little[j] && i + j < len)
			j++;
		if (j == n_len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
