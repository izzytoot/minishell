/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   80_free_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:06:36 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/23 14:58:24 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_msh(t_msh *msh)
{
	if (msh->envp_list)
		ft_lstclear(&msh->envp_list, free);
	if (msh->envp)
		ft_free_arrays((void *)msh->envp);
	if (msh->vars_list)
		ft_free_arrays((void *)msh->vars_list);
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
		safe_free((*msh)->prompt_line);
	if ((*msh)->tree_root)
	{
		free_tree((*msh)->tree_root);
		(*msh)->tree_root = NULL;
	}
//	if ((*msh)->token_list)
//		free_tokens((*msh)->token_list); //invalid and double frees because feed in tree. have to check
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
	if (node->op_content)
		safe_free(node->op_content);
	if (node->cmd_content)
		ft_free_str_arr(node->cmd_content);
	if (node->args && !node->cmd_content)
		ft_free_str_arr(node->args);
	if (node->tmp_file)
	{
		unlink(node->tmp_file);
		safe_free(node->tmp_file);
	}
	if (node->quote_lst)
		free_qt_lst(node->quote_lst);
	safe_free(node);
}
