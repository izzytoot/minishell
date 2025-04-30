/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   63_expand_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:24:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/30 18:05:02 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_final_cont(char *new_c, char *pre_c, char *post_c)
{
	char	*final_content;
	int		len;
	char	*tmp;
	char	*new_tmp;
	
	len = ft_strlen(new_c);
	if (len > 0 && new_c[len - 1] == '\n')
	{
		tmp = get_tmp(new_c, post_c, len);
		final_content = get_final(pre_c, tmp);
	}
	else
	{
		tmp = ft_strdup(new_c);
		if (pre_c)
			final_content = ft_strjoin(pre_c, tmp);
		else
			final_content = ft_strdup(tmp);
		if (post_c)
		{
			new_tmp = get_new_tmp(tmp, final_content);
			final_content = ft_strjoin(new_tmp, post_c);
		}
	}
	return(final_content);	
}

char	*get_tmp(char *new_c, char *post_c, int len)
{
	char	*tmp;
	
	if (post_c)			
		tmp = ft_strjoin(ft_substr(new_c, 0, len - 1), post_c);
	else
		tmp = ft_substr(new_c, 0, len - 1);
	return (tmp);
}

char	*get_final(char *pre_c, char *tmp)
{
	char	*final_content;
	
	if (pre_c)
		final_content = ft_strjoin(pre_c, tmp);
	else
		final_content = ft_strdup(tmp);
	return (final_content);
}

char	*get_new_tmp(char *tmp, char *f_c)
{
	char	*new_tmp;
	
	free(tmp);
	new_tmp = ft_calloc((ft_strlen(f_c) + 1), sizeof(char));
	new_tmp = ft_strdup(f_c);
	return (new_tmp);
}
