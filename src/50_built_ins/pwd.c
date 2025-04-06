/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/07 12:57:58 by icunha-t         ###   ########.fr       */
=======
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/06 20:47:43 by ddo-carm         ###   ########.fr       */
>>>>>>> 493c1e9 (echo and env updated to binary tree)
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
