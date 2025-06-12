/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:58:50 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/07 12:58:50 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_unset(t_msh **msh, t_tree_nd **node)
{
	int	i;

	if (!node || !*node || !(*node)->args)
		return (0);
	i = 0;
	if ((*node)->args)
	{
		while ((*node)->args[i])
		{
			if (ft_strncmp((*node)->args[i], "-", 1) == 0)
				return (0);
			ft_delete_env_var(&(*msh)->envp_list, (*node)->args[i]);
			ft_del_export_only(&(*msh)->export_only, (*node)->args[i]);
			ft_del_vars_list(&(*msh)->vars_list, (*node)->args[i]);
			i++;
		}
	}
	return (0);
}

void	ft_delete_env_var(t_list **env_list, const char *var_name)
{
	t_list	*current;
	t_list	*del;
	t_list	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (current->content && ft_strncmp((char *)current->content, var_name,
				ft_strlen(var_name)) == 0
			&& ((char *)current->content)[ft_strlen(var_name)] == '=')
		{
			del = current;
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			current = current->next;
			free(del->content);
			free(del);
			continue ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_del_export_only(t_list **export_only, const char *var_name)
{
	t_list	*tmp;
	t_list	*del;
	t_list	*prev;

	tmp = *export_only;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content && ft_strncmp((char *)tmp->content, var_name,
				ft_strlen(var_name + 2)) == 0)
		{
			del = tmp;
			if (prev)
				prev->next = tmp->next;
			else
				*export_only = tmp->next;
			tmp = tmp->next;
			free(del->content);
			free(del);
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_del_vars_list(t_list **vars_list, const char *var_name)
{
	t_list	*tmp;
	t_list	*del;
	t_list	*prev;

	tmp = *vars_list;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content && ft_strncmp((char *)tmp->content, var_name,
				ft_strlen(var_name)) == 0)
		{
			del = tmp;
			if (prev)
				prev->next = tmp->next;
			else
				*vars_list = tmp->next;
			tmp = tmp->next;
			free(del->content);
			free(del);
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
