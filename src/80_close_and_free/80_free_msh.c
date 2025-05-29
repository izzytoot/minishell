/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   80_free_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:06:36 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/29 17:36:14 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_msh(t_msh *msh)
{
	if (msh->envp_list)
		ft_lstclear(&msh->envp_list, free);
	if (msh->envp)
		ft_free_arrays((void *)msh->envp);
	if (msh->dir)
		msh->dir = safe_free(msh->dir);
	if (msh->vars_list)
		ft_free_arrays((void *)msh->vars_list);
	if (msh->tmp_fname)
		msh->tmp_fname = safe_free(msh->tmp_fname); //LEAKS
	if (msh->tree_root)
	{
		free_tree(msh->tree_root);
		msh->tree_root = NULL;
	}
	msh = safe_free(msh);
}

void	free_prompt_line(t_msh **msh)
{
	if ((*msh)->prompt_line)
		(*msh)->prompt_line = safe_free((*msh)->prompt_line);
	if ((*msh)->tree_root)
	{
		free_tree((*msh)->tree_root);
		(*msh)->tree_root = NULL;
	}
	(*msh)->hd_check = true;
	(*msh)->empties = false;
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
		node->file = safe_free(node->file);
	if (node->tmp_file)
	{
		unlink(node->tmp_file);
		node->tmp_file = safe_free(node->tmp_file);
	}
	if (node->op_content)
		node->op_content = safe_free(node->op_content);
	if (node->cmd) //LEAKS
		node->cmd = safe_free(node->cmd);
	if (node->args) //LEAKS
		ft_free_arrays((void **)node->args);
	if (node->cmd_content) //LEAKS
		ft_free_arrays((void **)node->cmd_content);
	/*if (node->cmd_content)
		ft_free_arrays((void **)node->cmd_content);
(node->cmd_content);
	if (node->args && !node->cmd_content)
		ft_free_arrays((void **)node->cmd_content);
(node->args);*/
	if (node->quote_lst)
		free_qt_lst(node->quote_lst);
	node = safe_free(node);
}
