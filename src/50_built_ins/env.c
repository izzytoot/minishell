/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:38:21 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/25 19:04:05 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_env(t_minishell **msh)
{
	int	i;
	t_list *temp;
	
	// if ((*msh)->token_list->content && (*msh)->token_list->next)
	// 	return (ft_putstr_fd(ERR_MANY_ARGS, STDERR_FILENO), 1);
	i = 0;
	if (!(*msh)->envp_list)
		return (EXIT_FAILURE);
	temp = (*msh)->envp_list;
	while(temp)
	{
		ft_putstr_fd(temp->content, STDOUT_FILENO);
		temp = temp->next;
	}
	return(EXIT_SUCCESS);
}
