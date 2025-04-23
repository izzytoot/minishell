/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   53_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/23 18:40:33 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array using binary tree

int	ft_echo(t_tree_nd **node)
{
	int		i;
	int		newline;

	i = 0;
	newline = 1;
	if (!node || !*node)
		return (EXIT_FAILURE);
	if ((*node)->args[0] && ft_strcmp((*node)->args[0], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while ((*node)->args[i])
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
