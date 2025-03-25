/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_debug_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:43:55 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/25 19:03:07 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_envp_in_struct(t_minishell **msh)
{
	t_list	*current = (*msh)->envp_list;
	while(current)
	{
		ft_printf(RED"%s\n"RES, current->content);
		current = current->next;
	}
	int	n = 0;
	while((*msh)->envp[n])
	{
		ft_printf(GR"%s\n"RES, (*msh)->envp[n]);
		n++;
	}
}

void	print_tokens(t_minishell **msh)
{
	t_token_lst	*current = (*msh)->token_list;
	int n = 0;
	char *token_type[] = {"PIPE", "WORD", "W_CMD", "W_ARG", "W_SPACE", "REDIR_IN", "REDIR_OUT", "REDIR_APP", "REDIR_HD", "ENV_VAR"};
	while(current)
	{
		ft_printf(YLL"token %d is"RES, ++n);
		ft_printf(BMAG" %s"RES, current->content);
		ft_printf(YLL" of type"RES);
		ft_printf(BMAG" %s\n"RES, token_type[current->type]);
		current = current->next;
	}
}

void	print_tree(t_tree_node *node, int depth)
{
	int	i = -1;

	if (!node) 
		return ;
	while(++i < depth)
		ft_printf("  ");
	i = 0;
	if (node->args != NULL)
	{
		ft_printf(GR"args - "RES);
		while (node->args[i])
		{
			ft_printf(BGR"[%s] "RES, node->args[i]);
			i++;
		}
		ft_printf("\n");
    }
	if (node->fd != 0)
	{
		ft_printf(GR"fd -"RES);
		ft_printf(BMAG" %i\n"RES, node->fd);
	}
	if (node->file != NULL)
	{
		ft_printf(GR"file -"RES);
		ft_printf(BMAG" %s\n"RES, node->file);
	}
	print_tree(node->left, (depth + 1));
    print_tree(node->right, (depth + 1));
}
