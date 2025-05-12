/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:30:52 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/05/09 16:41:49 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_is_directory(const char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}
