/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   52_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/07 23:50:11 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints env list

int	print_env(t_msh **msh, t_tree_nd **node)
{
	t_list	*current;

	if (!node || !*node)
		return (EXIT_FAILURE);
	if ((*node)->args[0])
	{
		ft_dprintf(STDERR_FILENO, "env: '%s': No such file or directory\n",
			(*node)->args[0]);
		return (EXIT_FAILURE);
	}
	current = (*msh)->envp_list;
	while (current)
	{
		ft_putstr_fd(current->content, STDOUT_FILENO);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

//info --> updates a var_name with new data

int	update_var(t_list **env_list, const char *var_name, const char *data)
{
	t_list	*current;
	size_t	var_name_len;
	char	*new_entry;
	char	*joined_value;

	var_name_len = ft_strlen(var_name);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->content, var_name, var_name_len) == 0
			&& ((char *)(current->content))[var_name_len] == '=')
		{
			free(current->content);
			joined_value = ft_strjoin(var_name, "=");
			new_entry = ft_strjoin(joined_value, data);
			free(joined_value);
			if (!new_entry)
				return (EXIT_FAILURE);
			current->content = new_entry;
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	add_new_var(env_list, var_name, data);
	return (EXIT_SUCCESS);
}

//info --> adds a new var_name with new data to the env list

void	add_new_var(t_list **env_list, const char *var_name,
			const char *data)
{
	char	*new_entry;
	char	*joined_value;

	joined_value = ft_strjoin(var_name, "=");
	new_entry = ft_strjoin(joined_value, data);
	free(joined_value);
	joined_value = NULL;
	if (!new_entry)
		return ;
	ft_lstadd_back(env_list, ft_lstnew(new_entry));
}

char	*get_var_val(t_list *env_list, const char *var_name)
{
	t_list	*curr;
	size_t	len;

	len = ft_strlen(var_name);
	curr = env_list;
    while (curr)
	{
		if (ft_strncmp(curr->content, var_name, len) == 0
            && ((char *)(curr->content))[len] == '=')
            return ((char *)(curr->content + len + 1));
        curr = curr->next;
    }
    return (NULL);
}
