/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   81_expand_fname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:43:18 by isabel            #+#    #+#             */
/*   Updated: 2025/06/06 17:42:29 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_fname(t_msh **msh, char **fname)
{
	t_exp_cont	parts;
	t_kw		*kw_lst;
	int			i;
	char		*tmp_fname;

	i = 0;
	ft_init_var((void **)&parts.pre_c, (void **)&parts.new_c,
		(void **)&parts.post_c, NULL);
	tmp_fname = ft_strdup(*fname);
	kw_lst = NULL;
	parts.pre_c = get_pre_cont(*fname, &i);
	build_kw_list(&kw_lst, *fname, &i);
	parts.post_c = get_post_cont(*fname, &i);
	expand_kw(msh, &kw_lst);
	parts.new_c = get_exp_cont(&kw_lst);
	subst_fname(fname, &parts);
	if (!(*fname))
		(*msh)->tmp_fname = tmp_fname;
	else
		tmp_fname = safe_free(tmp_fname);
	free_kw_structs(&parts, &kw_lst);
}

void	subst_fname(char **fname, t_exp_cont *parts)
{
	char	*final_c;

	final_c = NULL;
	if (parts->new_c)
	{
		final_c = get_final_cont(parts);
		*fname = safe_free((*fname));
		*fname = ft_strdup(final_c);
	}
	else if (parts->pre_c || parts->post_c)
	{
		if (parts->pre_c)
			final_c = ft_strdup(parts->pre_c);
		if (parts->post_c)
			final_c = ft_strjoin(final_c, ft_strdup(parts->post_c));
		*fname = safe_free((*fname));
		*fname = ft_strdup(final_c);
	}
	else
		*fname = safe_free(*fname);
	if (final_c)
		final_c = safe_free(final_c);
}

void	expand_and_join_fname(t_msh **msh, t_tk_lst *tmp_fn,
	t_tk_lst *merge_tg, bool hd_flag)
{
	t_tk_lst	*tmp_mg_prev;

	while (tmp_fn && (!tmp_fn->quotes.sp_case && tmp_fn->prev))
	{
		if (tk_in_qts(merge_tg))
			check_dollar_w_qts(&tmp_fn->content);
		expand_fn(msh, &tmp_fn, &merge_tg, hd_flag);
		join_parts(&tmp_fn, &merge_tg);
		if (!tmp_fn->quotes.sp_case && merge_tg->prev)
			rm_joined_tk(msh, &merge_tg, &tmp_fn, 1);
		else
		{
			if (!merge_tg->prev)
				rm_joined_tk(msh, &merge_tg, &tmp_fn, 2);
			else
			{
				tmp_mg_prev = merge_tg->prev;
				merge_tg->prev->next = tmp_fn;
				free_tokens(merge_tg, 1);
				tmp_fn->prev = tmp_mg_prev;
			}
			break ;
		}
	}
}
