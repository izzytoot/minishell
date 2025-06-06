/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   90_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:52:16 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/06 16:47:15 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_c_main(int sig)//C
{
	int	status;

	status = 0;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	if (WIFSIGNALED(sig))
		status = 128 + WTERMSIG(sig);
	exit_value(NULL, status, 1, 0);
}

void	ctrl_d_error(char *eof)
{
	ft_dprintf(STDERR_FILENO, ERR_HD_EOF);
	ft_dprintf(STDERR_FILENO, "(wanted '%s')\n", eof);
}
