/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/07 12:59:48 by icunha-t         ###   ########.fr       */
=======
/*   Updated: 2025/04/06 18:55:06 by ddo-carm         ###   ########.fr       */
>>>>>>> 52d9fa8 (norm in libft checked)
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

<<<<<<< HEAD
//info --> prints the array using binary tree
=======
//info --> prints the array using split (for test only)
/*
int	ft_echo(t_minishell **msh)
>>>>>>> 52d9fa8 (norm in libft checked)

int	ft_echo(t_tree_node **node)
{
	int		i;
	int		newline;

	i = 0;
	newline = 1;
	if (!node || !*node)
		return (EXIT_FAILURE);
	if ((*node)->args[1] && ft_strcmp((*node)->args[1], "-n") == 0)
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
<<<<<<< HEAD
=======

//info --> prints the array using binary tree
*/
int	ft_echo(t_minishell **msh)
{
	int 		i;
	int			newline;
	t_tree_node	*current;

	i = 0; // tem que ser 0
	newline = 1;
	current = (*msh)->tree_root; //temos que pensar como colocar este node como node atual e nao so a root
	if (current->type == PIPE)
		current = current->left;
	if (current->args[1] && ft_strcmp(current->args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (current->args[i])
	{
		ft_putstr_fd(current->args[i], STDOUT_FILENO);
		if ((*msh)->tree_root->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
>>>>>>> 52d9fa8 (norm in libft checked)
