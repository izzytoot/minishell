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
	while ((*node)->args[i])
	{
		if (ft_strncmp((*node)->args[i], "-", 1) == 0)
			return (0);
		ft_delete_var(&(*msh)->envp_list, (*node)->args[i]);
		i++;
	}
	return (0);
}

void	ft_delete_var(t_list **env_list, const char *var_name)
{
	t_list	*current;
	t_list	*del;
	t_list	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp((char *)current->content, var_name, ft_strlen(var_name))
			== 0 && ((char *)current->content)[ft_strlen(var_name)] == '=')
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
