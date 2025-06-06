/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   90_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:52:16 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/06 21:57:26 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_c_main(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit_value(NULL, 130, 1, 0);
}
void	sig_c_child(int sig)
{
	int	status;

	status = 128 + sig;
	ft_putstr_fd("\n", 1);
	exit_value(NULL, status, 1, 0);
}

t_msh	*get_msh(t_msh *msh, int flag)
{
	static t_msh	*ptr;

	if (flag)
		return (ptr);
	ptr = msh;
	return (ptr);
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
