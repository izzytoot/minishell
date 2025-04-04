/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:05:30 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/04 12:05:30 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_dprintf.h"

int	ft_dprint_char(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

int	ft_dprint_str(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_dprint_int(int nbr, int fd)
{
	unsigned int	nb;
	int				size;

	size = 0;
	if (nbr < 0)
	{
		nb = -nbr;
		size += ft_dprint_char('-', fd);
	}
	else
		nb = nbr;
	if (nb >= 10)
	{
		size += ft_dprint_int(nb / 10, fd);
	}
	size += ft_dprint_char((nb % 10) + '0', fd);
	return (size);
}

int	ft_dprint_unsign(unsigned int i, int fd)
{
	int	size;

	size = 0;
	if (i >= 10)
		size += ft_dprint_unsign(i / 10, fd);
	size += ft_dprint_char((i % 10) + '0', fd);
	return (size);
}
