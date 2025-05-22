/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   57_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:04:04 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/22 15:10:40 by icunha-t         ###   ########.fr       */
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
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
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
	return (exit_value(msh, 0, 1, 0), true);
}

void	add_export_var(t_list **env_list, const char *var_name,
	const char *data)
{
	char	*new_entry;
	char	*joined_value;
	t_list	*new_node;
	
	new_entry = NULL;
	joined_value = ft_strjoin(var_name, "=");
	if (data)
		new_entry = ft_strjoin(joined_value, data);
	else if (!data)
		new_entry = ft_strdup(joined_value);
	free(joined_value);
	joined_value = NULL;
	new_node = ft_lstnew(new_entry);
	if (!new_node)
	{
		free(new_entry);
		return ;
	}
	ft_lstadd_back(env_list, new_node);
}
