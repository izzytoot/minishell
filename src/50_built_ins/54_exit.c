/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   54_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:09:25 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/05 16:56:11 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> clean up and exit shell with correct value

void	ft_exit(t_msh **msh, t_tree_nd **node)
{
	unsigned char	exit_code;

	exit_code = 0;
	ft_printf("exit\n");
	if (!(*node)->args[0])
		exit_value(msh, exit_code, true, true);
	if (!ft_strnumeric((*node)->args[0], msh))
	{
		ft_dprintf(STDERR_FILENO,
			"msh: exit: %s: numeric argument required\n", (*node)->args[0]);
		exit_value(msh, 2, true, true);
	}
	else if ((*node)->args[1])
	{
		ft_dprintf(STDERR_FILENO, "msh: exit: too many arguments\n");
		exit_value(msh, 1, true, false);
	}
	else if (ft_convert_value(msh, (*node)->args[0]))
	{
		exit_value(msh, 0, false, true);
	}
}

//info --> convert the exit code given as arg into 8-bit unsigned integer

unsigned int	ft_convert_value(t_msh **msh, char *code)
{
	long long	nbr;

	nbr = ft_atoll(code);
	if (nbr == LLONG_MAX && ft_strcmp(code, "9223372036854775807"))
	{
		ft_dprintf(STDERR_FILENO, "msh: exit: %s: numeric argument required\n",
			code);
		return (exit_value(msh, 2, true, false));
	}
	if (nbr == LLONG_MIN && ft_strcmp(code, "-9223372036854775808"))
	{
		ft_dprintf(STDERR_FILENO, "msh: exit: %s: numeric argument required\n",
			code);
		return (exit_value(msh, 2, true, false));
	}
	if (!ft_strcmp(code, "-9223372036854775808"))
		exit_value(msh, 0, true, true);
	exit_value(msh, (unsigned char)nbr, true, false);
	return ((unsigned char)(nbr));
}

//info --> check if a str is numeric

int	ft_strnumeric(char *str, t_msh **msh)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
	{
		ft_dprintf(STDERR_FILENO, "msh: exit: %s: numeric argument required\n",
			str);
		return (exit_value(msh, 2, true, false));
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_dprintf(STDERR_FILENO,
				"msh: exit: %s: numeric argument required\n", str);
			return (exit_value(msh, 2, true, true));
		}
		i++;
	}
	return (true);
}
