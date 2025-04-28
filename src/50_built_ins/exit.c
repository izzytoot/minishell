/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:09:25 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/18 17:17:35 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> clean up and exit shell with correct value

void	ft_exit(t_minishell **msh, char **av)
{
	unsigned char	exit_code;

	exit_code = 0;
	ft_printf("exit\n");
	if (!av[1])
		ft_exit_value(*msh, exit_code, true, true);
	if (!ft_isalnum(av[1]))
	{
		ft_dprintf(STDERR_FILENO,
			"msh: exit: %s: numeric argument required", av[1]);
		ft_exit_value(*msh, 2, true, true);
	}
	else if (av[2])
	{
		perror("msh: exit:");
		ft_exit_value(*msh, 1, true, false);
	}
	else if (ft_convert_value(*msh, av[1], av));
	{
		ft_exit_value(*msh, 0, false, true);
	}
}

//info --> convert the exit code given as arg into 8-bit unsigned integer

static unsigned int	ft_convert_value(t_minishell **msh, char *code, char **av)
{
	long long	nbr;

	nbr = ft_atoll(code);
	if (nbr == LLONG_MAX && ft_strcmp(code, "9223372036854775807"))
	{
		ft_dprintf(STDERR_FILENO, "exit: %s: numeric argument required", code);
		return (ft_exit_value(*msh, 2, true, false));
	}
	ft_exit_value(*msh, (unsigned char)nbr, true, false);
	return (unsigned char)(nbr);
}


//info --> returns the current exit status,
//			with option to update it and exit the program

int	ft_exit_value(t_minishell **msh, int exit_code, int update_exit, int exit_msh)
{
	int	current_code;

	if (update_exit == true)
		current_code = exit_code;
	if (exit_msh == true)
		close_minishell(*msh, current_code);
	return (current_code);
}
