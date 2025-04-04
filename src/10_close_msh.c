/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_close_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/04 18:36:27 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_minishell(t_minishell	*msh, int exit_code)
{
	if (msh->active)
		free_msh(&(*msh));
	/*
	if (err_msg)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	*/
	strerror(errno);
	clear_history();
	exit(exit_code);
}

void	free_msh(t_minishell *msh)
{
	if (msh->envp_list)
		ft_lstclear(&msh->envp_list, free);
	if (msh->envp)
		ft_free_arrays((void *)msh->envp);
	free(msh);
}

void		handle_envp_failure(t_minishell *msh, char *str, t_list *list_node, char *array)
{
	if (str)
		free(str);
	if (list_node)
		free(list_node);
	if (array)
		free(array);
	close_minishell(msh, EXIT_FAILURE);
}

void	free_tokens(t_token_lst *token_list)
{
	t_token_lst *tmp;

	tmp = token_list;
	while(token_list)
	{
		tmp = token_list->next;
		if (token_list->content)
			free(token_list->content);
		free(token_list);
		token_list = tmp;
	}
}

void	free_prompt_line(t_minishell **msh)
{
	if ((*msh)->prompt_line)
	{
		free((*msh)->prompt_line);
		(*msh)->prompt_line = NULL;
	}
	if ((*msh)->token_list)
		free_tokens((*msh)->token_list);
	if ((*msh)->tree_root)
	{
		free_tree((*msh)->tree_root);
		(*msh)->tree_root = NULL;
	}
}

void	free_tree(t_tree_node *node)
{
	if (!node)
		return;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	if (node->file)
		free(node->file);
	if (node->op_content)
		free(node->op_content);
	if (node->cmd_content)
		ft_free_arrays((void **)node->cmd_content);
	if (node->args)
		ft_free_arrays((void **)node->args);
	free(node);
}
