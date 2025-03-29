/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/29 15:04:14 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints env list

int	print_env(t_minishell **msh)
{
	char	**args;
	
	args = ft_split((*msh)->promt_line, ' ');
	if (args && args[1])
	{
		if (access(args[1], F_OK) == -1)
		{
			errno = ENOENT;
			ft_putstr_fd("env: '", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd("': ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			return(ft_putstr_fd("\n", STDERR_FILENO), 1);
		}
	}
	if (!(*msh)->envp_list)
		return (EXIT_FAILURE);
	while ((*msh)->envp_list)
	{
		ft_putstr_fd((*msh)->envp_list->content, STDOUT_FILENO);
		(*msh)->envp_list = (*msh)->envp_list->next;
	}
	return (EXIT_SUCCESS);
}
