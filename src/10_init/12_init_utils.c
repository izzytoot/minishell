/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:16 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/19 18:44:37 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_getpid(t_minishell *msh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		close_minishell(msh, RED ERR_PRC RES, EXIT_FAILURE);
	wait (0);
	return (pid);	
}
