/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   70_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:01:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/10 00:52:32 by isabel           ###   ########.fr       */
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
				args_cpy[i] = tmp_arg;
				i++;
			}
			args_cpy[i] = NULL;
			node->quote_lst = tmp_qt;
			node->args = ft_array_dup(args_cpy);
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
			expand_tk(msh, arg, NULL);
		if ((*node)->quote_lst->next)
			(*node)->quote_lst = (*node)->quote_lst->next;
		else
			return ;
	}
}

void	subst_arg(char **arg, char *pre_c, char *new_c, char *post_c)
{
	char	*final_content;
	
	if (new_c)
	{
		final_content = get_final_cont(new_c, pre_c, post_c);
		//free(*arg);
		//*arg = final_content;
		*arg = ft_strdup(final_content);
	}
	else if(pre_c || post_c)
	{	
		if (pre_c)
			//final_content = pre_c;
			final_content = ft_strdup(pre_c);
		if (post_c)
		//	final_content = ft_strjoin(final_content, post_c);
			final_content = ft_strjoin(final_content, ft_strdup(post_c));
		//free(*arg);
		//*arg = final_content;
		*arg = ft_strdup(final_content);
	}
	else
		*arg = NULL;
}
