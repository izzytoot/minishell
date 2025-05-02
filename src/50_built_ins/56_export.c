/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   56_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:08:45 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/02 18:28:58 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*sort_env(t_list **env_list);

//info --> promotes a var to global

int	ft_export(t_msh **msh, t_tree_nd **node)
{
	t_list	*current;
	char	**var_info;
	int		i;
	
	if (!node || !*node)
		return (EXIT_FAILURE);
	if (!(*node)->args[0])
	{
		current = sort_env(&(*msh)->envp_list);
		while (current)
		{
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", (char *)current->content);
			current = current->next;
		}
		return (0);
	}
	else
	{
		i = 0;
		while ((*node)->args[i])
		{
			var_info = ft_split((*node)->args[i], '=');
			add_new_env_var(&(*msh)->envp_list, var_info[0], var_info[1]);
			i++;
		}
	}
	return (ft_free_arrays((void **)var_info), 0);
}

// void	disp_exported(t_msh **msh, t_tree_nd **node)
// {
// 	t_list	*current;
	
// 	if (!(*node)->args)
// 	{
// 		current = sort_env((*msh)->envp_list);
// 		while (current)
// 		{
// 			ft_dprintf(STDOUT_FILENO, "declare -x %s", (char *)current->content);
// 			current = current->next;
// 		}
// 	}
// }


t_list	*sort_env(t_list **env_list)
{
	t_list	*sorted;
	t_list	*temp;

	sorted = (*env_list);
	temp = (*env_list);
	while (env_list)
	{
		if (ft_strcmp((*env_list)->content, (*env_list)->next->content) > 0)
		{
			ft_printf("before sort: \n\n");
			ft_dprintf( STDOUT_FILENO, "sorted->content: %s", (char *)sorted->content);
			ft_dprintf( STDOUT_FILENO, "(*env_list)->content: %s", (char *)(*env_list)->content);
			ft_dprintf( STDOUT_FILENO, "sorted->next->content: %s", (char *)sorted->next->content);
			ft_dprintf( STDOUT_FILENO, "(*env_list)->next->content: %s", (char *)(*env_list)->next->content);
			temp->content = (*env_list)->content;
			sorted->content = (*env_list)->next->content;
			sorted->next->content = temp->content;
			ft_printf("after sort: \n\n");
			ft_dprintf( STDOUT_FILENO, "temp->content: %s", (char *)temp->content);
			ft_dprintf( STDOUT_FILENO, "sorted->content: %s", (char *)sorted->content);
			ft_dprintf( STDOUT_FILENO, "(*env_list)->content: %s", (char *)(*env_list)->content);
			ft_dprintf( STDOUT_FILENO, "sorted->next->content: %s", (char *)sorted->next->content);
			ft_dprintf( STDOUT_FILENO, "(*env_list)->next->content: %s", (char *)(*env_list)->next->content);
		}
		else
			sorted->content = (*env_list)->content;
		sorted = sorted->next;
		env_list = &(*env_list)->next;
	}
	return (sorted);
}
