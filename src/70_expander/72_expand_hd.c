/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   72_expand_hd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:43:50 by isabel            #+#    #+#             */
/*   Updated: 2025/05/11 21:07:26 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_line(t_msh **msh, t_hd_lines *lines,
	t_tree_nd *curr_nd, int hd_fd)
{
	(void)msh;
	int 	i;

	i = 0;
	if (!curr_nd->exp_hd || !count_exp(lines->new_l, 0)) 
		ft_putstr_fd(lines->new_l, hd_fd);
	else
	{
		lines->exp_newl = ft_split(lines->new_l, ' ');
		while (lines->exp_newl[i])
		{
			if (count_exp(lines->exp_newl[i], 0))
				lines->exp_newl[i] = expand_word(msh, lines->exp_newl[i]);
			i++;
		}
		ft_putstr_fd(ft_unsplit(lines->exp_newl), hd_fd);
	}
}

char	*expand_word(t_msh **msh, char *word)
{
	
	t_exp_cont	parts;
	t_kw		**kw_lst;
	int 	i;

	ft_init_var((void **)&parts.pre_c, (void **)&parts.new_c,
			(void **)&parts.post_c, NULL);
	i = 0;
	kw_lst = ft_calloc(MAX_KW, sizeof(t_kw *));
	if (word)
	{
		parts.pre_c = get_pre_cont(word, &i);
		build_kw_list(&(*kw_lst), word, &i);
		parts.post_c = get_post_cont(word, &i);
		expand_kw(msh, kw_lst);
		parts.new_c = get_exp_cont(kw_lst);
		subst_arg(&word, &parts);
	//	free_kw_structs(&parts, kw_lst);
	}
	else
		return (NULL);
	return (word);
}
