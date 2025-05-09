/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_expand_fname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:23:49 by isabel            #+#    #+#             */
/*   Updated: 2025/05/10 00:52:48 by isabel           ###   ########.fr       */
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
				expand_tk(msh, NULL, &node->file);
			i++;
		}
	}
	if (node->left)
		expand_files(msh, node->left);
	if(node->right)
		expand_files(msh, node->right);
}

void	subst_fname(char **fname, char *pre_c, char *new_c, char *post_c)
{
	char	*final_content;
	
	if (new_c)
	{
		final_content = get_final_cont(new_c, pre_c, post_c);
		//*fname = final_content;
		*fname = ft_strdup(final_content);
	}
	else if(pre_c || post_c)
	{	
		if (pre_c)
			//final_content = pre_c;	
			final_content = ft_strdup(pre_c);
		if (post_c)
			//final_content = ft_strjoin(final_content, post_c);
			final_content = ft_strjoin(final_content, ft_strdup(post_c));
		*fname = ft_strdup(final_content);
	}
	else
		*fname = NULL;
}
