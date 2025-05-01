/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   53_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/01 13:24:30 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array using binary tree
bool	handle_n(t_tree_nd **node, int *i);

int	ft_echo(t_tree_nd **node)
{
	int		i;
	bool	nline;

	i = 0;
	if (!node || !*node)
		return (EXIT_FAILURE);
	nline = handle_n(node, &i);
	while ((*node)->args[i])
	{
		ft_putstr_fd((*node)->args[i], STDOUT_FILENO);
		if ((*node)->args[i + 1] && (*node)->quote_lst && (*node)->quote_lst->next)
		{
			if ((!((*node)->quote_lst->in_quotes) && !((*node)->quote_lst->next->in_quotes))
					|| ((*node)->quote_lst->space_case))
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		i++;
		if ((*node)->quote_lst)
			(*node)->quote_lst = (*node)->quote_lst->next;
	}
	if (nline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

bool	handle_n(t_tree_nd **node, int *i)
{
	int		j;
	bool	newline;
	bool	first_flag;

	first_flag = true;
	while ((*node)->args[*i] && ft_strncmp((*node)->args[*i], "-n", 2) == 0)
	{
		j = 1;
		newline = false;
		while ((*node)->args[*i][j])
		{
			if ((*node)->args[*i][j] == 'n')
				j++;
			else if ((*node)->args[*i][j] != 'n')
			{
				if (first_flag)
					newline = true;
				return (newline);
			}
		}
		first_flag = false;
		(*i)++;
	}
	return (newline);
}
