/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   90_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:52:16 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/23 14:58:15 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signal_handler(int sig)
{
	int	status;

	status = 0;
	(void)sig;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	if (WIFSIGNALED(sig))
			status = 128 + WTERMSIG(sig);
	exit_value(NULL, status, 1, 0);
}
