/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   86_final_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:13 by isabel            #+#    #+#             */
/*   Updated: 2025/06/06 17:44:30 by ddo-carm         ###   ########.fr       */
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
		curr_c = safe_free(curr_c);
		curr_kw = curr_kw->next;
	}
	return (exp_c);
}

char	*get_final_cont(t_exp_cont *parts)
{
	char	*final_c;
	int		len;
	char	*tmp_new_c;

	len = ft_strlen(parts->new_c);
	if (len > 0 && parts->new_c[len - 1] == '\n')
	{
		tmp_new_c = get_tmp(parts->new_c, parts->post_c, len);
		final_c = ultimate_joint(parts->new_c, tmp_new_c);
	}
	else
		get_final_cont_util(&tmp_new_c, &final_c, parts);
	if (tmp_new_c)
		tmp_new_c = safe_free(tmp_new_c);
	return (final_c);
}

void	get_final_cont_util(char **tmp_new_c, char **final_c, t_exp_cont *parts)
{
	char	*tmp_final_c;

	*tmp_new_c = ft_strdup(parts->new_c);
	if (parts->pre_c)
		*final_c = ft_strjoin(parts->pre_c, *tmp_new_c);
	else
		*final_c = ft_strdup(*tmp_new_c);
	tmp_final_c = *final_c;
	if (parts->post_c)
	{
		*final_c = ft_strjoin(*final_c, parts->post_c);
		if (tmp_final_c)
			tmp_final_c = safe_free(tmp_final_c);
	}
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
