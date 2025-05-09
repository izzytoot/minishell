/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   73_expand_hd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:19:58 by isabel            #+#    #+#             */
/*   Updated: 2025/05/09 17:20:09 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_line(t_msh **msh, t_hd_lines *lines,
	t_tree_nd *curr_nd, int hd_fd)
{
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
	char	*pre_c;
	char	**kw;
	char	*post_c;
	char	*new_c;
	int 	i;

	ft_init_var((void **)&pre_c, (void **)&kw,
		(void **)&post_c, (void **)&new_c);
	i = 0;
	if (word)
	{
		pre_c = get_pre_cont(word, &i);
		kw = build_kw_array(word, &i);
		post_c = get_post_cont(word, &i);
		new_c = build_new_arg(msh, kw);
		subst_arg(&word, pre_c, new_c, post_c);
	}
	else
		return (NULL);
	return (word);
}