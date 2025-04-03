/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/07 12:18:51 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array using split (for test only)

int	ft_echo(t_minishell **msh)

{
	int		i;
	int		newline;
	char	**args;

	args = ft_split((*msh)->promt_line, ' ');
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args [i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

//info --> prints the array using binary tree
*/
void	ft_echo(t_minishell **msh)
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
}
