/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   53_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/29 17:11:42 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array using binary tree
int	handle_n(t_tree_nd **node);

int	ft_echo(t_tree_nd **node)
{
	int		i;
	t_quote	*quote;
	bool	newline;

	if (!node || !*node)
		return (EXIT_FAILURE);
	newline = true;
	i = handle_n(node);
	if (i > 0)
		newline = false;
	quote = (*node)->quote_lst;
	for (int j = 0; j < i && quote; j++)
		quote = quote->next;
	while ((*node)->args[i])
	{
		ft_putstr_fd((*node)->args[i], STDOUT_FILENO);
		if ((*node)->args[i + 1] && quote && quote->next)
		{
			if (!(quote->in_quotes && quote->next->in_quotes))
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		i++;
		if (quote)
			quote = quote->next;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	handle_n(t_tree_nd **node)
{
	int	i;

	i = 0;
	while ((*node)->args[i] && ft_strncmp((*node)->args[i], "-n", 2) == 0)
	{
		i++;
	}
	return (i);
}
