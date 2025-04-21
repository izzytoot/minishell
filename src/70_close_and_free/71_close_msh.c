/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_close_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/21 14:08:36 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_minishell(t_msh *msh, int exit_code)
{
	if (msh->active)
		free_msh(&(*msh));
	strerror(errno);
	clear_history();
	exit(exit_code);
}

void	envp_fail(t_msh *msh, char *str, t_list *list_nd, char *array)
{
	if (str)
		free(str);
	if (list_nd)
		free(list_nd);
	if (array)
		free(array);
	close_minishell(msh, EXIT_FAILURE);
}
