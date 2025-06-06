/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:40:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/04 14:31:19 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_trimmed(char **tr_s1, char **tr_s2)
{
	if (tr_s1)
		*tr_s1 = safe_free(*tr_s1);
	if (tr_s2)
		*tr_s2 = safe_free(*tr_s2);
}

char	*join_both(char *s1, char *s2)
{
	char	*tr_s1;
	char	*tr_s2;
	char	*res;
	int		len;

	len = ft_strlen(s1);
	tr_s1 = NULL;
	tr_s2 = NULL;
	if (len > 0 && s1[len - 1] == '\n')
		tr_s1 = ft_substr(s1, 0, len - 1);
	else if (len > 0 && s1[len - 1] != '\n')
		tr_s1 = ft_strdup(s1);
	else if (len == 0)
		return (s2);
	len = ft_strlen(s2);
	if (len > 0 && s2[len - 1] == '\n')
		tr_s2 = ft_substr(s2, 0, len - 1);
	else if (len > 0 && s2[len - 1] != '\n')
		tr_s2 = ft_strdup(s2);
	else if (len == 0)
		return (tr_s1);
	res = ft_strjoin(tr_s1, tr_s2);
	free_trimmed(&tr_s1, &tr_s2);
	s1 = safe_free(s1);
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
			return (s1);
	}
	else
		return (join_both(s1, s2));
}
