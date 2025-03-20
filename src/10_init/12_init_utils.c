/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:16 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/20 12:30:58 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_all_null (t_minishell **msh)
{
	(*msh)->dir = NULL;
	(*msh)->msh_pid = 0;
	(*msh)->promt_line = NULL;
	(*msh)->token_list = NULL;
	(*msh)->envp = NULL;
	(*msh)->envp_list = NULL;
}

int	my_getpid(t_minishell *msh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		close_minishell(msh, RED ERR_PRC RES, EXIT_FAILURE);
	wait (0);
	return (pid);	
}
