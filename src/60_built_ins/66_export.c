/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   66_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:08:45 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/06 19:43:38 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> promotes a var to global

int	ft_export(t_msh **msh, t_tree_nd **node, int i, int valid_export)
{
	char	**var_info;
	char	*s_qt_info;
	t_quote	*tmp_lst;
	
	if (!node || !*node)
		return (EXIT_FAILURE);
	if (!(*node)->args)
		return (disp_exported(msh), 0);
	tmp_lst = (*node)->quote_lst;
	while ((*node)->args && (*node)->args[i])
	{
		if (!export_check(msh, tmp_lst->in_squotes, (*node)->args[i]))
		{
			i++;
			tmp_lst = tmp_lst->next;
			continue ;
		}
		if (((*node)->args && (*node)->args[i]) && (tmp_lst->next && tmp_lst->next->in_squotes))
		{
			s_qt_info = ft_strjoin((*node)->args[i], (*node)->args[i + 1]);
			var_info = ft_split(s_qt_info, '=');
			s_qt_info = safe_free(s_qt_info);
		}
		else
			var_info = ft_split((*node)->args[i], '=');
		if (!tmp_lst->in_squotes && (*node)->args && is_single_exp((*node)->args[i]))
			add_only_to_export(*msh, (*node)->args[i]);
		else
			add_export_var(&(*msh)->envp_list, var_info[0], var_info[1]);
		ft_free_arrays((void **)var_info);
		valid_export = 1;
		i++;
		tmp_lst = tmp_lst->next;
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
