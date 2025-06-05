/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   56_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:08:45 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/05 23:15:38 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> promotes a var to global

int	ft_export(t_msh **msh, t_tree_nd **node, int i, int	valid_export)
{
	char	**var_info;

	if (!node || !*node)
		return (EXIT_FAILURE);
	if (!(*node)->args[0])
		return (disp_exported(msh), 0);
	while ((*node)->args[i])
	{
		if (!export_check(msh, (*node)->args[i]))
		{
			i++;
			continue ;
		}
		var_info = ft_split((*node)->args[i], '=');
		if (is_single_exp((*node)->args[i]))
			add_only_to_export(*msh, (*node)->args[i]);
		else
			add_export_var(&(*msh)->envp_list, var_info[0], var_info[1]);
		ft_free_arrays((void **)var_info);
		valid_export = 1;
		i++;
	}
	if (!valid_export && i == 1)
		return (1);
	return (0);
}

void	disp_exported(t_msh **msh)
{
	t_list	*current;
	char	*equal_sign;
	int		name_len;
	char	*var_name;

	current = sort_env((*msh)->envp_list, 1);
	while (current)
	{
		equal_sign = ft_strchr(current->content, '=');
		if (equal_sign)
		{
			name_len = ft_strlen_until(current->content, '=');
			var_name = ft_substr(current->content, 0, name_len);
			if (!var_name)
				return ;
			ft_dprintf(STDOUT_FILENO, "declare -x %s=\"%s\"\n",
				var_name, equal_sign + 1);
			free(var_name);
		}
		else
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", current->content);
		current = current->next;
	}
	print_only_export(*msh);
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
	char	*content_dup;

	cpy = NULL;
	while (env_list)
	{
		content_dup = ft_strdup((char *)env_list->content);
		if (!content_dup)
		{
			ft_lstclear(&cpy, free);
			return (NULL);
		}
		new = ft_lstnew(content_dup);
		if (!new)
		{
			free(content_dup);
			ft_lstclear(&cpy, free);
			return (NULL);
		}
		ft_lstadd_back(&cpy, new);
		env_list = env_list->next;
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
