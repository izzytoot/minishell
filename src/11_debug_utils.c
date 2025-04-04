/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_debug_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:43:55 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/04 17:01:58 by icunha-t         ###   ########.fr       */
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
	char *node_type[] = {"PIPE", "WORD", "BT_CMD", "ARG", "W_SPACE", "FILE_NAME", "REDIR_IN", "REDIR_OUT", "REDIR_APP", "REDIR_HD", "ENV_CMD"};

	if (!node) 
		return ;
	i = -1;
	if (type_is_redir(&node->type))
	{
		ft_printf(YLL"deatils of branch"RES);
		ft_printf(BMAG" %s %s "RES, node->op_content, node->file);
		ft_printf("\n");
		if (node->fd == 0 || node->fd)
		{
			ft_printf(GR"fd -"RES);
			ft_printf(BMAG" %i\n"RES, node->fd);
		}
		if (node->file)
		{
			ft_printf(GR"file -"RES);
			ft_printf(BMAG" %s"RES, node->file);
			ft_printf("\n");
		}
	}
	else if (!node->left && !node->right)
	{
		if (type_is_word(&node->type) && !node->cmd)
			return ;
		ft_printf(YLL"deatils of branch"RES);
		if (node->type == PIPE)
			ft_printf(BMAG" %s \n"RES, node->op_content);
		else if(type_is_word(&node->type) && node->cmd)
		{
			while (node->cmd_content[++i])
				ft_printf(BMAG" %s"RES, node->cmd_content[i]);
			ft_printf("\n");
			if (node->cmd)
			{
				ft_printf(GR"cmd - "RES);
				ft_printf(BMAG"[%s]\n"RES, node->cmd);
				ft_printf(GR"type - "RES);
				ft_printf(BMAG"%s\n"RES, node_type[node->type]);
			}
			i = -1;
			if (node->args)
			{
				ft_printf(GR"args - "RES);
				while (node->args[++i])
					ft_printf(BMAG"[%s] "RES, node->args[i]);
			}
			ft_printf("\n");
		}
	}
	if (node->right)
	{
		if (type_is_word(&node->right->type) && !node->right->cmd)
			return ;
		if (type_is_redir(&node->type) || node->type == PIPE)
			ft_printf(GR"right branch of [%s] is:"RES, node->op_content);
		else
		{
			i = -1;
			ft_printf(GR"right branch of"RES);
			while (node->cmd_content[++i])
				ft_printf(BMAG" %s"RES, node->cmd_content[i]);
			ft_printf(GR" is:"RES);
		}	
		if (type_is_redir(&node->right->type))
			ft_printf(BMAG" %s %s "RES, node->right->op_content, node->right->file);
		else if (node->right->type == PIPE)
			ft_printf(BMAG" %s"RES, node->right->op_content);
		else
		{
			i = -1;
			while (node->right->cmd_content[++i])
				ft_printf(BMAG" %s"RES, node->right->cmd_content[i]);
		}	
		ft_printf("\n");
	}
	if (node->left)
	{
		if (type_is_word(&node->left->type) && !node->left->cmd)
			return;
		if (type_is_redir(&node->type) || node->type == PIPE)
			ft_printf(GR"left branch of [%s] is:"RES, node->op_content);
		else
		{
			i = -1;
			ft_printf(GR"left branch of"RES);
			while (node->cmd_content[++i])
				ft_printf(BMAG" %s"RES, node->cmd_content[i]);
			ft_printf(GR" is:"RES);
		}	
		if (type_is_redir(&node->left->type))
			ft_printf(BMAG" %s %s "RES, node->left->op_content, node->left->file);
		else if (node->left->type == PIPE)
			ft_printf(BMAG" %s"RES, node->left->op_content);
		else
		{
			i = -1;
			while (node->left->cmd_content[++i])
				ft_printf(BMAG" %s"RES, node->left->cmd_content[i]);
		}	
		ft_printf("\n");
	}
   	if (node->right)
	{
		ft_printf(BBLU"-----------------------------\n"RES);
		print_tree(node->right);
	}
	if (node->left)
	{
		ft_printf(BBLU"-----------------------------\n"RES);
		print_tree(node->left);
	}
}

