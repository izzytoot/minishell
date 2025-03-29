/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/29 16:34:54 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array

void	ft_echo(t_minishell **msh)
{
	int i;

	i = 0;
	while ((*msh)->tree_root->args[i])
	{
		if ((*msh)->tree_root->type == WORD && ft_strncmp((*msh)->tree_root->args[2], "echo", 4) == 0)
		{
			
			ft_putstr_fd((*msh)->tree_root->args[i], STDOUT_FILENO);
			if ((*msh)->tree_root->args[i + 1])
				ft_putstr_fd(" ", STDOUT_FILENO);
			if (!(*msh)->tree_root->args[i + 1])
				ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
}
