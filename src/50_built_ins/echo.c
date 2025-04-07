/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/07 16:49:08 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array using binary tree

int	ft_echo(t_tree_node **node)
{
	int		i;
	int		total_args;
	int		newline;

	i = 0;
	total_args = 0;
	newline = 1;
	if (!node || !*node)
		return (EXIT_FAILURE);
	while ((*node)->args[total_args])
		total_args++;
	total_args--;
	if (ft_strcmp((*node)->args[total_args], "-n") == 0)
		newline = 0;
	while ((*node)->args[i] && i < total_args)
	{
		ft_putstr_fd((*node)->args[i], STDOUT_FILENO);
		if ((*node)->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
