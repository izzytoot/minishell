/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/30 15:10:51 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints env list

int	print_env(t_minishell **msh)
{
	t_list	*current;
	char	**args;
	
	args = ft_split((*msh)->promt_line, ' ');
	if (args && args[1])
	{
			ft_putstr_fd("env: '", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
			ft_free_arrays((void **)args);
			return(EXIT_FAILURE);
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
