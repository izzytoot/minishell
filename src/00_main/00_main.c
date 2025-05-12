/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:28:40 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/12 14:05:16 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_msh	*msh;

	(void)ac;
	(void)av;
	msh = ft_calloc(1, sizeof(t_msh));
	if (!msh)
		close_minishell(msh, EXIT_FAILURE);
	msh->active = true;
	msh->debug_mode = false; //DELETE BEFORE SUMISSION
	ft_init_msh(&msh, envp);
	return (0);
}
