/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_close_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/29 16:25:34 by icunha-t         ###   ########.fr       */
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

	free(msh->dir);
	ft_lstclear(&msh->envp_list, free);
	ft_free_arrays((void *)msh->envp);
	if (msh->token_list)
		free_tokens(msh->token_list); // it's only freeing 1 side of tree for now
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
		free(token_list->content);
		free(token_list);
		token_list = tmp;
	}
}