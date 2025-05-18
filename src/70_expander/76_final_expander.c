/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   76_final_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:13 by isabel            #+#    #+#             */
/*   Updated: 2025/05/18 18:23:25 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_exp_cont(t_kw **kw_lst)
{
	char	*exp_c;
	char	*curr_c;
	t_kw	*curr_kw;

	ft_init_var((void **)&exp_c, (void **)&curr_c, NULL, NULL);
	curr_kw = *kw_lst;
	while (curr_kw)
	{
		curr_c = ft_strdup(curr_kw->kw);
		exp_c = safe_strjoin(exp_c, curr_c);
		curr_kw = curr_kw->next;
	}
	return (exp_c);
}

char	*get_final_cont(t_exp_cont *parts)
{
	char	*final_c;
	int		len;
	char	*tmp;

	len = ft_strlen(parts->new_c);
	if (len > 0 && parts->new_c[len - 1] == '\n')
	{
		tmp = get_tmp(parts->new_c, parts->post_c, len);
		final_c = ultimate_joint(parts->new_c, tmp);
	}
	else
	{
		tmp = ft_strdup(parts->new_c);
		if (parts->pre_c)
			final_c = ft_strjoin(parts->pre_c, tmp);
		else
			final_c = ft_strdup(tmp);
		if (parts->post_c)
			final_c = ft_strjoin(final_c, parts->post_c);
	}
	return (final_c);
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

char	*ultimate_joint(char *pre_c, char *tmp)
{
	char	*final_content;

	if (pre_c)
		final_content = ft_strjoin(pre_c, tmp);
	else
		final_content = ft_strdup(tmp);
	return (final_content);
}
