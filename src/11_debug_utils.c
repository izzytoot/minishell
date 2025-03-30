/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_debug_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:43:55 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/29 17:12:43 by icunha-t         ###   ########.fr       */
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
	char *token_type[] = {"PIPE", "WORD", "BT_CMD", "ARG", "W_SPACE", "FILE_NAME", "REDIR_IN", "REDIR_OUT", "REDIR_APP", "REDIR_HD", "ENV_CMD"};
	while(current)
	{
		ft_printf(YLL"token %d is"RES, ++n);
		ft_printf(BMAG" %s"RES, current->content);
		ft_printf(YLL" of type"RES);
		ft_printf(BMAG" %s\n"RES, token_type[current->type]);
		current = current->next;
	}
}

void	print_tree(t_tree_node *node)
{
	int	i = -1;

	if (!node) 
		return ;
	i = 0;
	if (node->args)
	{
		ft_printf(GR"args - "RES);
		while (node->args[i])
		{
			ft_printf(BMAG"[%s] "RES, node->args[i]);
			i++;
		}
		ft_printf("\n");
    }
	if (node->fd)
	{
		ft_printf(GR"fd -"RES);
		ft_printf(BMAG" %i\n"RES, node->fd);
	}
	if (node->file)
	{
		ft_printf(GR"file -"RES);
		ft_printf(BMAG" %s\n"RES, node->file);
	}
	i = -1;
	if (node->left)
	{
		ft_printf(GR"left branch is:\n"RES);
		while (node->left->args[++i])
			ft_printf(BMAG" %s "RES, node->left->args[i]);
		ft_printf("\n");
	}
	i = -1;
	if (node->right)
	{
		ft_printf(GR"right branch is:\n"RES);
		while (node->left->args[++i])
			ft_printf(BMAG" %s "RES, node->right->args[i]);
		ft_printf("\n");
	}
	print_tree(node->left);
    print_tree(node->right);
}
