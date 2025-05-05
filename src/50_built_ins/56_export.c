/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   56_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:08:45 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/05 15:59:17 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> promotes a var to global

int	ft_export(t_msh **msh, t_tree_nd **node)
{
	char	**var_info;
	int		i;
	
	if (!node || !*node)
		return (EXIT_FAILURE);
	if (!(*node)->args[0])
	{
		disp_exported(msh);
		return (0);
	}
	else
	{
		i = 0;
		while ((*node)->args[i])
		{
			var_info = ft_split((*node)->args[i], '=');
			add_new_env_var(&(*msh)->envp_list, var_info[0], ft_strjoin(var_info[1], "\n"));
			i++;
		}
	}
	return (ft_free_arrays((void **)var_info), 0);
}

void	disp_exported(t_msh **msh)
{
	t_list	*current;
	
	current = sort_env((*msh)->envp_list);
	while (current)
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s", (char *)current->content);
		current = current->next;
	}
}

t_list	*sort_env(t_list *env_list)
{
	t_list	*current;
	char	*temp;
	int 	sorted;

	if (!env_list)
		return (NULL);
	sorted = 1;
	while (sorted)
	{
		sorted = 0;
		current = env_list;
		while (current->next)
		{
			if (ft_strcmp((char *)current->content, (char *)current->next->content) > 0)
			{
				temp = current->content;
				current->content = current->next->content;
				current->next->content = temp;
				sorted = 1;
			}
			current = current->next;
		}
	}
	return (env_list);
}
