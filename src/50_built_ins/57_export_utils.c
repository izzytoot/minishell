/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   57_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:04:04 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/05 18:38:37 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (false);
		if (!ft_isalnum(arg[i]) && arg[i] != '_') //if single quotes
			return (false);
		i++;
	}
	if (arg[i] == '+' && arg[i + 1] != '=')
		return (false);
	return (true);
}

bool	export_check(t_msh **msh, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_dprintf(STDERR_FILENO, "msh: export: `%s': not a valid identifier\n",
			arg);
		exit_value(msh, 1, 1, 0);
		return (false);
	}
	exit_value(msh, 0, 1, 0);
	return (true);
}

void	add_export_var(t_list **env_list, const char *var_name, const char *data)
{
	t_list	*current;
	size_t	var_len;
	char	*new_entry;
	t_list	*new_node;

	var_len = ft_strlen(var_name);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->content, var_name, var_len) == 0
			&& ((char *)current->content)[var_len] == '=')
		{
			free(current->content);
			current->content = update_var_util(var_name, data);
			return ;
		}
		current = current->next;
	}
	new_entry = update_var_util(var_name, data);
	if (!new_entry)
		return ;
	new_node = ft_lstnew(new_entry);
	if (!new_node)
		return (free(new_entry));
	ft_lstadd_back(env_list, new_node);
}
