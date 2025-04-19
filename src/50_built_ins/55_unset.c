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

//info --> delete the content of a var

int	ft_unset(t_minishell **msh, t_tree_node **node)
{
	int	i;

	if (!node || !*node || !(*node)->args)
		return (0);
	i = 0;
	while ((*node)->args[i])
	{
		ft_delete_var(&(*msh)->envp_list, (*node)->args[i]);
		i++;
	}
	return (0);
}

//info --> delete a env var, free it's memory

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
