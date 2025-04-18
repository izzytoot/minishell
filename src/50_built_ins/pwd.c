/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/18 12:35:26 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		ft_printf("%s\n", path);
	else
		strerror(errno);
	return (0);
}
