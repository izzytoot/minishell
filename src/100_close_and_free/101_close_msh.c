/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   81_close_msh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/22 21:24:49 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_minishell(t_msh *msh, int exit_code)
{
	if (msh->active)
		free_msh(&(*msh));
	strerror(errno);
	clear_history();
	exit (exit_code);
}

void	envp_fail(t_msh *msh, char *str, t_list *list_nd, char **array)
{
	if (str)
		safe_free(str);
	if (list_nd)
		safe_free(list_nd);
	if (array)
		safe_free(array);
	close_minishell(msh, EXIT_FAILURE);
}
