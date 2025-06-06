/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   80_expand_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:01:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 17:41:49 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_args(t_msh **msh, t_tree_nd *node)
{
	char	**args_cpy;
	t_quote	*tmp_qt;

	if (!node)
		return ;
	if ((type_is_word(&node->type) && node->args))
	{
		tmp_qt = node->quote_lst;
		args_cpy = ft_calloc((node->nb_arg + 1), sizeof(char *));
		expand_loop(msh, node, args_cpy);
		node->quote_lst = tmp_qt;
		if (node->args)
			ft_free_array_w_null(node->args, node->nb_arg);
		node->args = ft_array_dup_null(node, args_cpy, node->nb_arg);
		ft_free_arrays((void **)args_cpy);
	}
	recurs_exp_args(msh, node);
}

void	expand_loop(t_msh **msh, t_tree_nd *node, char **args_cpy)
{
	char	*tmp_arg;
	int		i;

	i = -1;
	while (node->args[++i])
	{
		if (!node->quote_lst->sp_case && node->quote_lst->next
			&& !node->quote_lst->in_quotes && node->quote_lst->next->in_quotes)
		{
			if (check_dollar_w_qts(&node->args[i]))
			{
				node->quote_lst->sp_case = node->quote_lst->next->sp_case;
				node->quote_lst = node->quote_lst->next;
			}
		}
		if (!node->args[i])
			continue ;
		tmp_arg = ft_strdup(node->args[i]);
		expander(msh, &node, &tmp_arg);
		args_cpy[i] = tmp_arg;
	}
	args_cpy[i] = NULL;
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
		while ((*arg)[j] && !ft_strchr("$", (*arg)[j]))
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
	int			i;
	t_exp_cont	parts;
	t_kw		*kw_lst;

	ft_init_var((void **)&parts.pre_c, (void **)&parts.new_c,
		(void **)&parts.post_c, NULL);
	i = 0;
	kw_lst = NULL;
	parts.pre_c = get_pre_cont(*arg, &i);
	build_kw_list(&kw_lst, *arg, &i);
	parts.post_c = get_post_cont(*arg, &i);
	expand_kw(msh, &kw_lst);
	parts.new_c = get_exp_cont(&kw_lst);
	subst_arg(arg, &parts);
	free_kw_structs(&parts, &kw_lst);
}

void	subst_arg(char **arg, t_exp_cont *parts)
{
	char	*final_c;

	final_c = NULL;
	if (parts->new_c)
	{
		final_c = get_final_cont(parts);
		*arg = safe_free(*arg);
		*arg = ft_strdup(final_c);
	}
	else if (parts->pre_c || parts->post_c)
	{
		if (parts->pre_c)
			final_c = ft_strdup(parts->pre_c);
		if (parts->post_c)
			final_c = ft_strjoin(final_c, ft_strdup(parts->post_c));
		*arg = safe_free(*arg);
		*arg = ft_strdup(final_c);
	}
	else
		*arg = safe_free(*arg);
	if (final_c)
		final_c = safe_free(final_c);
}
