/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   66_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:08:45 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/08 22:21:45 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export(t_msh **msh, t_tree_nd **node, int i, int valid_export)
{
	char	**var_inf;
	t_quote	*tmp_lst;

	if (!node || !*node)
		return (EXIT_FAILURE);
	if (!(*node)->args)
		return (disp_exported(msh, 0), 0);
	var_inf = NULL;
	tmp_lst = (*node)->quote_lst;
	while ((*node)->args && (*node)->args[i])
	{
		if (!export_check(msh, &tmp_lst, (*node)->args[i]))
		{
			move_on(&i, &tmp_lst);
			continue ;
		}
		get_var_info(node, tmp_lst, i, &var_inf);
		ft_export_util(msh, tmp_lst->in_squotes, (*node)->args[i], var_inf);
		ft_free_arrays((void **)var_inf);
		valid_export = 1;
		move_on(&i, &tmp_lst);
	}
	if (!valid_export && i == 1)
		return (1);
	return (0);
}

void	disp_exported(t_msh **msh, int name_len)
{
	t_list	*current;
	t_list	*head;
	char	*equal;
	char	*var;

	current = sort_env((*msh)->envp_list, 1);
	head = current;
	while (current)
	{
		equal = ft_strchr(current->content, '=');
		if (equal)
		{
			name_len = ft_strlen_until(current->content, '=');
			var = ft_substr(current->content, 0, name_len);
			if (!var)
				return ;
			ft_dprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n", var, equal + 1);
			free(var);
		}
		else
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", current->content);
		current = current->next;
	}
	print_only_export(*msh);
	free_and_clear(NULL, head);
}

t_list	*sort_env(t_list *env_list, int sort)
{
	t_list	*sorted;
	t_list	*current;
	char	*temp;

	sorted = copy_env_list(env_list);
	if (!env_list)
		return (NULL);
	while (sort)
	{
		sort = 0;
		current = sorted;
		while (current->next)
		{
			if (ft_strcmp((char *)current->content,
					(char *)current->next->content) > 0)
			{
				temp = current->content;
				current->content = current->next->content;
				current->next->content = temp;
				sort = 1;
			}
			current = current->next;
		}
	}
	return (sorted);
}

t_list	*copy_env_list(t_list *env_list)
{
	t_list	*cpy;
	t_list	*new;
	t_list	*env_list_tmp;
	char	*content_dup;

	cpy = NULL;
	env_list_tmp = env_list;
	while (env_list_tmp)
	{
		content_dup = ft_strdup((char *)env_list_tmp->content);
		if (!content_dup)
		{
			free_and_clear(NULL, cpy);
			return (NULL);
		}
		new = ft_lstnew(content_dup);
		if (!new)
		{
			free_and_clear(content_dup, cpy);
			return (NULL);
		}
		ft_lstadd_back(&cpy, new);
		env_list_tmp = env_list_tmp->next;
	}
	return (cpy);
}

void	print_only_export(t_msh	*msh)
{
	t_list	*curr;

	curr = msh->export_only;
	while (curr)
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s\n", (char *)curr->content);
		curr = curr->next;
	}
}
