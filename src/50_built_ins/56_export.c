/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   56_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:08:45 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/22 17:01:46 by ddo-carm         ###   ########.fr       */
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
		return (disp_exported(msh), 0);
	else
	{
		i = 0;
		while ((*node)->args[i])
		{
			if (!export_check(msh, (*node)->args[i]))
				return (exit_value(msh, 1, 1, 0));
			var_info = ft_split((*node)->args[i], '=');
			add_export_var(&(*msh)->envp_list, var_info[0], var_info[1]);
			i++;
		}
	}
	return (ft_free_arrays((void **)var_info), 0);
}

void	disp_exported(t_msh **msh)
{
	t_list	*current;
	char	*equal_sign;
	int		name_len;

	current = sort_env((*msh)->envp_list, 1);
	while (current)
	{
		equal_sign = ft_strchr(current->content, '=');
		if (equal_sign)
		{
			name_len = ft_strlen_until(current->content, '=');
			write(STDOUT_FILENO, "declare -x ", 12);
			write(STDOUT_FILENO, current->content, name_len);
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, equal_sign + 1, ft_strlen(equal_sign + 1));
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", current->content);
		current = current->next;
	}
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

	cpy = NULL;
	while (env_list)
	{
		new = ft_lstnew(ft_strdup((char *)env_list->content));
		if (!new)
			return (NULL);
		ft_lstadd_back(&cpy, new);
		env_list = env_list->next;
	}
	return (cpy);
}
