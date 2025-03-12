/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_close_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/12 17:02:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_minishell(t_minishell	*msh, char *err_msg, int exit_code)
{
	if (msh->active)
		free_msh(&(*msh));
	if (err_msg)
		ft_putstr_fd(err_msg, 2);
	exit(exit_code);
}

void	free_msh(t_minishell *msh)
{
	free(msh->prog_name);
	ft_lstclear(&msh->l_envp, free);
	free(msh);
}

void	handle_envp_failure(t_minishell *msh, char *str, t_list *list_node)
{
	if (str)
		free(str);
	if (list_node)
		free(list_node);
	close_minishell(msh, RED ERR_ENVP RES, EXIT_FAILURE);
}