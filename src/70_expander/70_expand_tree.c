/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   70_expand_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:01:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/01 17:56:56 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_tree(t_msh **msh, t_tree_nd *node)
{
	char	**args_cpy;
	char	*tmp_arg;
	int		i;
	t_quote	*tmp_qt;

	i = 0;
	if (!node)
		return ;
	if ((type_is_word(&node->type) && node->args))
	{
			tmp_qt = node->quote_lst;
			args_cpy = ft_calloc((node->nb_arg + 1), sizeof(char *));
			while (node->args[i])
			{
				tmp_arg = ft_strdup(node->args[i]);
				expander(msh, &node, &tmp_arg);
				args_cpy[i] = tmp_arg;
				i++;
			}
			args_cpy[i] = NULL;
			node->quote_lst = tmp_qt;
			node->args = args_cpy;
	}
	recurs_exp_tree(msh, node);
}

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

void	expander(t_msh **msh, t_tree_nd **node, char **arg)
{
	int	j;

	j = 0;
	if ((*node)->quote_lst->in_squotes)
	{
		if ((*node)->quote_lst->next)
		{
			(*node)->quote_lst = (*node)->quote_lst->next;
			return ;
		}
		else
			return ;
	}
	else
	{
		while((*arg)[j] && !ft_strchr("$", (*arg)[j]))
		 	++j;
		if ((*arg)[j] == '$')
			expand_tk(msh, arg, NULL);
		if ((*node)->quote_lst->next)
			(*node)->quote_lst = (*node)->quote_lst->next;
		else
			return ;
	}
}
