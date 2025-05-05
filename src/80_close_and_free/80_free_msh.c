/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   80_free_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:06:36 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/02 16:44:30 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_msh(t_msh *msh)
{
	if (msh->envp_list)
		ft_lstclear(&msh->envp_list, free);
	if (msh->envp)
		ft_free_arrays((void *)msh->envp);
	if (msh->tree_root)
	{
		free_tree(msh->tree_root);
		msh->tree_root = NULL;
	}
	free(msh);
}

void	free_prompt_line(t_msh **msh)
{
	if ((*msh)->prompt_line)
	{
		free((*msh)->prompt_line);
		(*msh)->prompt_line = NULL;
	}
	if ((*msh)->tree_root)
	{
		free_tree((*msh)->tree_root);
		(*msh)->tree_root = NULL;
	}
	if ((*msh)->token_list)
		free_tokens((*msh)->token_list);
	(*msh)->hd_check = true;
//	safe_dup2(0, STDIN_FILENO, getpid()); //check if needed
//	safe_dup2(1, STDOUT_FILENO, getpid()); //check if needed
}

void	free_tokens(t_tk_lst *token_list)
{
	t_tk_lst	*tmp;

	tmp = token_list;
	while (token_list)
	{
		tmp = token_list->next;
		if (token_list->content)
			free(token_list->content);
		free(token_list);
		token_list = tmp;
	}
}

void	free_tree(t_tree_nd *node)
{
	if (!node)
		return ;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	if (node->file)
		free(node->file);
	if (node->op_content)
		free(node->op_content);
	if (node->cmd_content != node->args)
		ft_free_arrays((void **)node->cmd_content);
	if (node->args)
		ft_free_arrays((void **)node->args);
	if(node->tmp_file)
	{
		unlink(node->tmp_file);
		free(node->tmp_file);
	}
	free(node);
}
