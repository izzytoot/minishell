/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:40:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/10 20:39:03 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*join_both(char *s1, char *s2)
{
	char	*tr_s1;
	char	*tr_s2;
	char	*res;
	int		len;

	len = ft_strlen(s1);
	if (len > 0 && s1[len - 1] == '\n')
		tr_s1 = ft_substr(s1, 0, len - 1);
	else if (len > 0 && s1[len - 1] != '\n')
		tr_s1 = ft_strdup(s1);
	len = ft_strlen(s2);
	if (len > 0 && s2[len - 1] == '\n')
		tr_s2 = ft_substr(s2, 0, len - 1);
	else if (len > 0 && s2[len - 1] != '\n')
		tr_s2 = ft_strdup(s2);
	res = ft_strjoin(tr_s1, tr_s2);
	return (res);
}

char	*safe_strjoin(char *s1, char *s2)
{
	int		len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		len = ft_strlen(s2);
		if (len > 0 && s2[len - 1] == '\n')
			return (ft_substr(s2, 0, len - 1));
		else
			return (ft_strdup(s2));
	}
	else if (!s2)
	{
		len = ft_strlen(s1);
		if (len > 0 && s1[len - 1] == '\n')
			return (ft_substr(s1, 0, len - 1));
		else
			return (ft_strdup(s1));
	}
	else
		return (join_both(s1, s2));
}
