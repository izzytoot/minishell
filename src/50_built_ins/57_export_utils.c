/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   57_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:04:04 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/12 21:18:48 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	if (arg[i] == '+' && arg[i + 1] != '=')
		return (false);
	return (true);
}

bool	export_check(t_msh **msh, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_dprintf(STDERR_FILENO, "msh: export: `%s': not a valid identifier\n",
			arg);
		exit_value(msh, 1, 1, 0);
		return (false);
	}
	return (exit_value(msh, 0, 1, 0), true);
}
