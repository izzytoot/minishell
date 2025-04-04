/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:28:40 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/07 12:25:12 by icunha-t         ###   ########.fr       */
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
		close_minishell(msh, EXIT_FAILURE);
	msh->active = true;
	msh->debug_mode = true; //DELETE BEFORE SUMISSION
	ft_init_msh(&msh, envp);
	return(0);
}
