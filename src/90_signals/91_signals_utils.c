/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   91_signals_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:58:26 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/11 18:31:14 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 100)
	{
		close(fd);
		fd++;
	}
}

void	ctrl_d_error(char *eof)
{
	ft_dprintf(STDERR_FILENO, ERR_HD_EOF);
	ft_dprintf(STDERR_FILENO, "(wanted '%s')\n", eof);
}

t_msh	*get_msh(t_msh *msh, int flag)
{
	static t_msh	*ptr;

	if (flag)
		return (ptr);
	ptr = msh;
	return (ptr);
}

void	sig_cmd_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, sig_ig);
}
