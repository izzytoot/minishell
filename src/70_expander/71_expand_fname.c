/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_expand_fname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:43:18 by isabel            #+#    #+#             */
/*   Updated: 2025/05/12 15:51:40 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_files(t_msh **msh, t_tree_nd *node)
{
	int		i;
	
	i = 0;
	if (!node)
		return ;
	if ((type_is_redir(&node->type) && node->file) && node->type != REDIR_HD)
	{
		while (node->file[i])
		{
			if (node->file[i] == '$')
				expand_fname(msh, &node->file);
			i++;
		}
	}
	if (node->left)
		expand_files(msh, node->left);
	if(node->right)
		expand_files(msh, node->right);
}

void	expand_fname(t_msh **msh, char **fname)
{
	t_exp_cont	parts;
	t_kw		**kw_lst;
	int 		i;

	ft_init_var((void **)&parts.pre_c, (void **)&parts.new_c,
		(void **)&parts.post_c, NULL);
	i = -1;
	kw_lst = ft_calloc(MAX_KW, sizeof(t_kw *));
	parts.pre_c = get_pre_cont(*fname, &i);
	build_kw_list(&(*kw_lst), *fname, &i);
	parts.post_c = get_post_cont(*fname, &i);
	expand_kw(msh, kw_lst);
	parts.new_c = get_exp_cont(kw_lst);
	subst_fname(fname, &parts);
//	free_kw_structs(&parts, kw_lst);
}

void	subst_fname(char **fname, t_exp_cont *parts)
{
	char	*final_c;
	
	if (parts->new_c)
	{
		final_c = get_final_cont(parts);
		*fname = ft_strdup(final_c);
	}
	else if(parts->pre_c || parts->post_c)
	{	
		if (parts->pre_c)
			final_c = ft_strdup(parts->pre_c);
		if (parts->post_c)
			final_c = ft_strjoin(final_c, ft_strdup(parts->post_c));
		*fname = ft_strdup(final_c);
	}
	else
		*fname = NULL;
}
