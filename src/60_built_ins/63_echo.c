/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   63_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/03 17:36:29 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> prints the array using binary tree

int	ft_echo(t_tree_nd **node)
{
	int		i;
	bool	nline;
	bool	first_flag;
	t_quote	*tmp_lst; //leaks - added var to equal tmp_lst
	
	i = 0;
	first_flag = true;
	nline = true;
	if (!node || !*node)
		return (EXIT_FAILURE);
	if ((*node)->args) //leaks - added line
		nline = handle_n(node, &i, first_flag);
	while ((*node)->args && (*node)->args[i]) //leaks - added (*node)->args && 
	{
		tmp_lst = (*node)->quote_lst;
		ft_putstr_fd((*node)->args[i], STDOUT_FILENO);
		if ((*node)->args[i + 1] && tmp_lst
			&& tmp_lst->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
		tmp_lst = tmp_lst->next; //leaks , removed if next
	}
	if (nline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

bool	handle_n(t_tree_nd **node, int *i, bool first_flag)
{
	int		j;
	bool	newline;
	t_quote	*tmp_lst;
	
	newline = true;
	tmp_lst = (*node)->quote_lst;
	while ((*node)->args[*i] && ft_strncmp((*node)->args[*i], "-n", 2) == 0)
	{
		j = 1;
		newline = false;
		while ((*node)->args[*i][j])
		{
			if ((*node)->args[*i][j] == 'n')
				j++;
			else if ((*node)->args[*i][j] != 'n')
				return (get_newline(first_flag, &newline)); //leaks reduced lines with new funct
		}
		first_flag = false;
		(*i)++;
		if (tmp_lst->next)
			tmp_lst = tmp_lst->next;
	}
	return (newline);
}

bool	get_newline(bool first_flag, bool *newline)
{
	if (first_flag)
		*newline = true;
	return (*newline);
}
