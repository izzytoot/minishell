/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_close_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/11 18:42:45 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_minishell(t_minishell	*msh, char *err_msg, int exit_code)
{
	int	i;

	i = 0;
	if (msh)
		free_msh(&msh);
	if (err_msg)
		ft_putstr_fd(err_msg, 2);
	exit(exit_code);
}

void	free_msh(t_minishell *msh)
{
	ft_lstclear(&msh->envp, free);
}