/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_envp_copies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:44:25 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/30 11:50:55 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	copy_envp(t_msh *msh, char **envp)
{
	if (!envp)
		return ;
	msh->envp = envp_to_array(msh, envp);
	msh->envp_list = NULL;
	envp_to_list(msh, envp);
}

char	**envp_to_array(t_msh *msh, char **envp)
{
	int		i;
	int		count;
	char	**envp_array;

	i = -1;
	count = 0;
	while (envp[count])
		count++;
	envp_array = ft_calloc((count + 1), sizeof(char *));
	if (!envp_array)
		envp_fail(msh, NULL, NULL, NULL);
	while (++i < count)
	{
		envp_array[i] = ft_strdup(envp[i]);
		if (!envp_array)
		{
			while (--i >= 0)
				free(envp_array[i]);
			free(envp_array);
			envp_fail(msh, NULL, NULL, NULL);
		}
	}
	envp_array[count] = NULL;
	return (envp_array);
}

void	envp_to_list(t_msh *msh, char **envp)
{
	int		i;
	char	*temp_envp;
	t_list	*new_node;

	i = -1;
	ft_init_var((void **)&temp_envp, (void **)&new_node, NULL, NULL);
	while (envp[++i])
	{
		temp_envp = ft_strdup(envp[i]);
		if (!temp_envp)
			envp_fail(msh, temp_envp, NULL, NULL);
		new_node = ft_lstnew(temp_envp);
		if (!new_node)
		{
			free(temp_envp);
			envp_fail(msh, NULL, new_node, NULL);
		}
		ft_lstadd_back(&msh->envp_list, new_node);
	}
}

char	**cpy_for_execve(t_msh **msh)
{
	int		i;
	int		len;
	char	**envp_array;
	t_list	*current;

	i = 0;
	len = ft_lstsize((*msh)->envp_list);
	envp_array = malloc(sizeof(char *) * (len + 1));
	if (!envp_array)
		envp_fail(*msh, NULL, NULL, NULL);
	current = (*msh)->envp_list;
	while (current)
	{
		envp_array[i] = ft_strdup((char *)current->content);
		if (!envp_array[i])
			envp_fail(*msh, NULL, NULL, envp_array);
		current = current->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

void	env_i(t_list **env_list)
{
	char	*pwd_value;
	char	*_value;
	char	cwd[PATH_MAX];

	pwd_value = get_var_val(*env_list, "PWD");
	_value = get_var_val(*env_list, "_");
	if (!pwd_value || !_value)
	{
		if (!getcwd(cwd, sizeof(cwd)))
			return ;
		update_var(env_list, "PWD", cwd);
		update_var(env_list, "_", "/usr/bin/env");
	}
	return ;
}
