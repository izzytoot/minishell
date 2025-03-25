/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/25 18:44:30 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_env(t_minishell **msh)
{
	int	i;
	
	// if ((*msh)->token_list->content && (*msh)->token_list->next)
	// 	return (ft_putstr_fd(ERR_MANY_ARGS, STDERR_FILENO), 1);
	i = 0;
	if (!(*msh)->envp)
		return (EXIT_FAILURE);
	while(&(*msh)->envp[i])
	{
		ft_putstr_fd((*msh)->envp[i], STDOUT_FILENO);
		i++;
	}
	return(EXIT_SUCCESS);
}
