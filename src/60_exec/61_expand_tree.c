/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   61_expand_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:01:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/30 18:04:43 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_tree(t_msh **msh, t_tree_nd *node)
{
	char	**args_cpy;
	char	*tmp_arg;
	int	i;
	t_quote	*tmp_qt;

	i = 0;
	if (!node)
		return ;
	if (type_is_cmd(&node->type) || node->type == ARG)
	{
		if (node->args)
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
	//		ft_free_arrays((void **)node->args);
	//		free(tmp_qt);
			node->args = args_cpy;
		}
	}
	recurs_exp_tree(msh, node);	
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
	char	*pre_c;
	char	**kw;
	char	*post_c;
	char	*new_c;
	int		i;
	int	k;
	int	tmp_i;
	int	count;
	char *new_arg;
	int	n;

	n = 0;
	i = -1;
	k = 0;
	pre_c = get_pre_cont(*arg, &i);
	tmp_i = i;
	count = 0;
	char *s = *arg;
	while(s[i] && !ft_strchr(WHITESPACE, s[i]))
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	if (count)
		kw = calloc((count + 1), sizeof(char *));
	i = tmp_i;
	while(s[i] && !ft_strchr(WHITESPACE, s[i]))
	{
		if (s[i] == '$')
			kw[k] = get_key_word(s, &i);
		k++;
	}
	kw[k] = NULL;
	post_c = get_post_cont(*arg, &i);
	i = 0;
	new_arg = NULL;
	while(i < k)
	{
		if (special_exp(msh, &new_c, kw[i]) == 1)
			;
		else if (special_exp(msh, &new_c, kw[i]) == 3)
			new_c = get_env_cont((*msh)->envp_list, kw[i]);
		if(!new_c)
			new_c = NULL;
		new_arg = safe_strjoin(new_arg, new_c);
		if (new_c)
			new_c = NULL;
		i++;
		n++;
	}
	subst_arg(arg, pre_c, new_arg, post_c);
	ft_free_arrays((void **)kw);
}

int	special_exp(t_msh **msh, char **new_cont, char *kw)
{
	if (!kw || ft_strchr(WHITESPACE, kw[0]) || !kw[0])
		return (1);
	if (ft_strcmp(kw, "0") == 0)
	{
		*new_cont = ft_strdup("minishell");
		return (2);
	}
	else if(ft_strcmp(kw, "?") == 0)
	{
		*new_cont = ft_strdup(ft_itoa(exit_value(msh, 0, 0, 0)));
		return (2);
	}
	return (3);
}

void	subst_arg(char **arg, char *pre_c, char *new_c, char *post_c)
{
	char	*final_content;
	
	if (new_c)
	{
		final_content = get_final_cont(new_c, pre_c, post_c);
		free(*arg);
		*arg = ft_strdup(final_content);
	}
	else if(pre_c || post_c)
	{	
		if (pre_c)
			final_content = ft_strdup(pre_c);
		if (post_c)
			final_content = ft_strjoin(final_content, ft_strdup(post_c));
		free(*arg);
		*arg = ft_strdup(final_content);
	}
	else
		*arg = NULL;
}
