/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_debug_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:43:55 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/12 16:41:18 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_envp_in_struct(t_msh **msh)
{
	t_list	*curr = (*msh)->envp_list;
	while(curr)
	{
		ft_printf(RED"%s\n"RES, curr->content);
		curr = curr->next;
	}
	int	n = 0;
	while((*msh)->envp[n])
	{
		ft_printf(GR"%s\n"RES, (*msh)->envp[n]);
		n++;
	}
}

void	print_tokens(t_msh **msh)
{
	t_tk_lst	*curr = (*msh)->token_list;
	int n = 0;
	char *token_type[] = {"PIPE", "WORD", "BT_CMD", "ARG", "W_SPACE", "FILE_NAME", "REDIR_IN", "REDIR_OUT", "REDIR_APP", "REDIR_HD", "ENV_CMD"};
	while(curr)
	{
		ft_printf(YLL"token %d is"RES, ++n);
		ft_printf(BMAG" %s"RES, curr->content);
		ft_printf(YLL" of type"RES);
		ft_printf(BMAG" %s "RES, token_type[curr->type]);
		if (curr->quotes.in_dquotes)
		{
			ft_printf(YLL"and it's in "RES);
			ft_printf(BMAG"double quotes\n"RES);
		}
		else if (curr->quotes.in_squotes)
		{
			ft_printf(YLL"and it's in "RES);
			ft_printf(BMAG"single quotes\n"RES);
		}
		else
		{
			ft_printf(YLL"and it's "RES);
			ft_printf(BMAG"not in quotes\n"RES);
		}
		curr = curr->next;
	}
}

void	print_tree(t_tree_nd *node)
{
	int	i = -1;
	char *node_type[] = {"PIPE", "WORD", "BT_CMD", "ARG", "W_SPACE", "FILE_NAME", "REDIR_IN", "REDIR_OUT", "REDIR_APP", "REDIR_HD", "ENV_CMD"};

	if (!node) 
		return ;
	i = -1;
	if (type_is_redir(&node->type))
	{
		ft_printf(GR"details of branch"RES);
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
		ft_printf(GR"details of branch"RES);
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
