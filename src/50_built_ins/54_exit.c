/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   54_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:09:25 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/12 23:55:54 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> clean up and exit shell with correct value

int	ft_exit(t_msh **msh, t_tree_nd **node)
{
	unsigned char	exit_code;
	char			**args;

	args = (*node)->args;
	ft_printf("exit\n");
	if (args[0] && ft_strcmp(args[0], "--") == 0)
		args++;
	if (!args[0])
		exit_value(msh, exit_value(msh, 0, false, false), true, true);
	if (!ft_strnumeric(args[0]))
	{
		ft_dprintf(STDERR_FILENO,
			"msh: exit: %s: numeric argument required\n", args[0]);
		exit_value(msh, 2, true, true);
	}
	if (args[1])
	{
		ft_dprintf(STDERR_FILENO, "msh: exit: too many arguments\n");
		exit_value(msh, 1, true, false);
		return (1);
	}
	exit_code = ft_convert_value(msh, args[0]);
	exit_value(msh, exit_code, true, true);
	return (exit_code);
}

//info --> convert the exit code given as arg into 8-bit unsigned integer

unsigned int	ft_convert_value(t_msh **msh, char *code)
{
	long long	nbr;

	nbr = ft_atoll(code);
	if ((nbr == LLONG_MAX && ft_strcmp(code, "9223372036854775807"))
		|| (nbr == LLONG_MIN && ft_strcmp(code, "-9223372036854775808")))
	{
		ft_dprintf(STDERR_FILENO, "msh: exit: %s: numeric argument required\n",
			code);
		exit_value(msh, 2, true, true);
	}
	return ((unsigned char)nbr);
}

//info --> check if a str is numeric

int	ft_strnumeric(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
