/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/26 18:22:13 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array

void	ft_echo(t_minishell **msh)
{
	int	i;
	char **args;

	args = ft_split((*msh)->promt_line, ' ');
	i = 1;
	while (args[i])
	{
		// ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args [i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		if (!args [i + 1])
			ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}
