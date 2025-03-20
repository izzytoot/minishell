/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_close_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/20 12:32:54 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_minishell(t_minishell	*msh, char *err_msg, int exit_code)
{
	if (msh->active)
		free_msh(&(*msh));
	if (err_msg)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	clear_history();
	exit(exit_code);
}

void	free_msh(t_minishell *msh)
{

	free(msh->dir);
	ft_lstclear(&msh->envp_list, free);
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
	close_minishell(msh, RED ERR_ENVP RES, EXIT_FAILURE);
}
