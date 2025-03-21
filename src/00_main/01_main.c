/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:28:40 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/21 17:04:10 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		main(int ac, char **av, char **envp)
{
	t_minishell	*msh;
	
	(void)ac;
	(void)av;
	msh = ft_calloc(1, sizeof(t_minishell));
	if (!msh)
		close_minishell(msh, RED ERR_MEM RES, EXIT_FAILURE);
	msh->active = true;
	msh->debug_mode = true; //DELETE BEFORE SUMISSION
	ft_init_msh(&msh, envp);
	close_minishell(msh, NULL, EXIT_SUCCESS);
	return(0);
}
