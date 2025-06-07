/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   90_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:52:16 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/07 16:00:28 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_c_main(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
	exit_value(NULL, 130, 1, 0);
}
void	sig_c_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit_value(NULL, 130, 1, 0);
}

void	ctrl_c_hd(int sig)
{
	t_msh	*msh;
	
	(void)sig;
	msh = NULL;
	msh = get_msh(NULL, 1);
	ft_putstr_fd("\n", 1);
	close_fds();
	exit_value(&msh, 130, 1, 1);
}
