/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/07 12:25:41 by icunha-t         ###   ########.fr       */
=======
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/04 17:32:34 by ddo-carm         ###   ########.fr       */
>>>>>>> 509bd70 (added dprintf, and did norm on libft)
=======
/*   Updated: 2025/04/06 21:26:03 by ddo-carm         ###   ########.fr       */
>>>>>>> 493c1e9 (echo and env updated to binary tree)
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints env list

int	print_env(t_minishell **msh, t_tree_node **node)
{
<<<<<<< HEAD
	t_list	*current;

<<<<<<< HEAD
	if (!node || !*node)
=======
	args = ft_split((*msh)->promt_line, ' ');
	if (args && args[1])
	{
		ft_dprintf(STDERR_FILENO, "env: '%s': No such file or directory\n", args[1]);
		ft_free_arrays((void **)args);
>>>>>>> 509bd70 (added dprintf, and did norm on libft)
		return (EXIT_FAILURE);
	if ((*node)->args[0])
	{
=======
	t_list *current;

	if (!node || !*node)
		return (1);
	if ((*node)->args)
	{
>>>>>>> 493c1e9 (echo and env updated to binary tree)
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

//info --> adds a new var_name with new data to the env list

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
