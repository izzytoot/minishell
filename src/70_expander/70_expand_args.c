/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   70_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:01:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/18 21:09:43 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_args(t_msh **msh, t_tree_nd *node)
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
				//tmp_arg = node->args[i];
				tmp_arg = ft_strdup(node->args[i]);
				expander(msh, &node, &tmp_arg);
				args_cpy[i] = tmp_arg; //strdup??
				i++;
			}
			args_cpy[i] = NULL;
			node->quote_lst = tmp_qt;
			node->args = ft_array_dup_w_null(node, args_cpy, node->nb_arg);
	}
	recurs_exp_args(msh, node);
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
			expand_tk(msh, arg);
		if ((*node)->quote_lst->next)
			(*node)->quote_lst = (*node)->quote_lst->next;
		else
			return ;
	}
}

void	expand_tk(t_msh **msh, char **arg)
{
	t_exp_cont	parts;
	t_kw		**kw_lst;
	int 		i;

	ft_init_var((void **)&parts.pre_c, (void **)&parts.new_c,
		(void **)&parts.post_c, NULL);
	i = -1;
	kw_lst = ft_calloc(MAX_KW, sizeof(t_kw *));
	parts.pre_c = get_pre_cont(*arg, &i);
	build_kw_list(&(*kw_lst), *arg, &i);
	parts.post_c = get_post_cont(*arg, &i);
	expand_kw(msh, kw_lst);
	parts.new_c = get_exp_cont(kw_lst);
	subst_arg(arg, &parts);
	free_kw_structs(&parts, kw_lst);
}

void	subst_arg(char **arg, t_exp_cont *parts)
{
	char	*final_c;
	
	if (parts->new_c)
	{
		final_c = get_final_cont(parts);
		*arg = ft_strdup(final_c);
	}
	else if(parts->pre_c || parts->post_c)
	{	
		if (parts->pre_c)
			final_c = ft_strdup(parts->pre_c);
		if (parts->post_c)
			final_c = ft_strjoin(final_c, ft_strdup(parts->post_c));
		*arg = ft_strdup(final_c);
	}
	else
		*arg = NULL;
}

char	**ft_array_dup_w_null(t_tree_nd *node, char **array, int n)
{
	int		i;
	int		size;
	char	**new_array;

	if (!array)
		return (NULL);
	size = 0;
	i = 0;
	while (n-- > 0)
	{
		if (array[i])
			size++;
		i++;
	}
	node->nb_arg = size;
	new_array = copy_array(size, array);
	return (new_array);
}
