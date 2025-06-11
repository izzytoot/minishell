/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/11 17:52:39 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_env(t_msh **msh, t_tree_nd **node)
{
	t_list	*current;
	char	*clean;

	if (!node || !*node)
		return (EXIT_FAILURE);
	if ((*node)->args && (*node)->args[0])
	{
		ft_dprintf(STDERR_FILENO, "env: '%s': No such file or directory\n",
			(*node)->args[0]);
		return (EXIT_FAILURE);
	}
	current = (*msh)->envp_list;
	while (current)
	{
		clean = ft_strtrim((char *)current->content, "\n");
		ft_printf("%s\n", clean);
		free(clean);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	update_var(t_list **env_list, const char *var_name, const char *data)
{
	t_list	*current;
	size_t	var_name_len;
	char	*new_entry;

	if (!var_name || !env_list)
		return (EXIT_FAILURE);
	var_name_len = ft_strlen(var_name);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->content, var_name, var_name_len) == 0
			&& ((char *)(current->content))[var_name_len] == '=')
		{
			free(current->content);
			new_entry = update_var_util(var_name, data);
			if (!new_entry)
				return (EXIT_FAILURE);
			current->content = new_entry;
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (add_new_var(env_list, var_name, data), EXIT_SUCCESS);
}

char	*update_var_util(const char *var_name, const char *data)
{
	char	*joined_value;
	char	*new_entry;

	joined_value = ft_strjoin(var_name, "=");
	if (!joined_value)
		return (NULL);
	if (!data)
		new_entry = ft_strdup(joined_value);
	else
		new_entry = ft_strjoin(joined_value, data);
	free(joined_value);
	return (new_entry);
}

int	add_new_var(t_list **env_list, const char *var_name,
			const char *data)
{
	char	*new_entry;
	char	*joined_value;
	t_list	*new_node;

	joined_value = ft_strjoin(var_name, "=");
	if (!joined_value)
		return (EXIT_FAILURE);
	new_entry = ft_strjoin(joined_value, data);
	free(joined_value);
	joined_value = NULL;
	if (!new_entry)
		return (EXIT_FAILURE);
	new_node = ft_lstnew(new_entry);
	if (!new_node)
	{
		free(new_entry);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(env_list, new_node);
	return (EXIT_SUCCESS);
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
