/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/04 17:35:24 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints env list

int	print_env(t_minishell **msh)
{
	t_list	*current;
	char	**args;

	args = ft_split((*msh)->prompt_line, ' ');
	if (args && args[1])
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		ft_free_arrays((void **)args);
		return (EXIT_FAILURE);
	}
	if (!(*msh)->envp_list)
	{
		ft_free_arrays((void **)args);
		return (EXIT_FAILURE);
	}
	current = (*msh)->envp_list;
	while (current)
	{
		ft_putstr_fd(current->content, STDOUT_FILENO);
		current = current->next;
	}
	return (ft_free_arrays((void **)args), EXIT_SUCCESS);
}

//info --> updates a var_name with new data

int	update_env_var(t_list **env_list, const char *var_name, const char *data)
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
	add_new_env_var(env_list, var_name, data);
	return (EXIT_SUCCESS);
}

void	add_new_env_var(t_list **env_list, const char *var_name,
			const char *data)
{
	char	*new_entry;
	char	*joined_value;

	joined_value = ft_strjoin(var_name, "=");
	new_entry = ft_strjoin(joined_value, data);
	free(joined_value);
	if (!new_entry)
		return ;
	ft_lstadd_back(env_list, ft_lstnew(new_entry));
}
