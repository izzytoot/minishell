/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/03 17:38:50 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_work_dir(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		ft_printf("%s\n", path);
	else
		strerror(errno);
	return (0);
}
