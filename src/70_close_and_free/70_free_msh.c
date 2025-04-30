/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   70_free_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:06:36 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/30 10:38:52 by isabel           ###   ########.fr       */
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
	safe_free(msh);
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
	if ((*msh)->token_list)
		free_tokens((*msh)->token_list);
	(*msh)->hd_check = true;
	if ("/tmp/.heredoc_tmp")
		unlink("/tmp/.heredoc_tmp");
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
			safe_free(token_list->content);
		safe_free(token_list);
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
		safe_free(node->file);
	if (node->op_content)
		safe_free(node->op_content);
	if (node->cmd_content != node->args)
		ft_free_arrays((void **)node->cmd_content);
	if (node->args)
		ft_free_arrays((void **)node->args);
	safe_free(node);
}
