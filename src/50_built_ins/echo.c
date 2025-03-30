/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/30 17:59:55 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


//info --> prints the array using split (for test only)

void	ft_echo(t_minishell **msh)

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
}


//info --> prints the array using binary tree

// void	ft_echo(t_minishell **msh)
// {
// 	int 		i;
// 	int			newline;
// 	t_tree_node	*current;
	
// 	i = 1;
// 	newline = 1;
// 	current = (*msh)->tree_root;
// 	if (current->type == PIPE)
// 		current = current->left;
// 	ft_printf("arg[0] is %s arg[1] is %s", current->args[0], current->args[1]);
// 	if (current->args[1] && ft_strcmp(current->args[1], "-n") == 0)
// 	{
// 		newline = 0;
// 		i++;
// 	}
// 	while (current->args[i])
// 	{
// 		ft_putstr_fd(current->args[i], STDOUT_FILENO);
// 		if ((*msh)->tree_root->args[i + 1])
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	if (newline)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// }
