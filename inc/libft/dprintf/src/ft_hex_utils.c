/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:03:51 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/04 12:03:51 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_dprintf.h"

static int	ft_ptr_util(unsigned long ptr, int fd)
{
	int		size;
	char	*hex;

	hex = "0123456789abcdef";
	size = 0;
	if (ptr >= 16)
		size += ft_ptr_util(ptr / 16, fd);
	size += ft_dprint_char(hex[ptr % 16], fd);
	return (size);
}

int	ft_dprint_ptr(unsigned long ptr, int fd)
{
	char	*hex;
	int		size;

	hex = "0123456789abcdef";
	if (!ptr)
		return (ft_dprint_str("(nil)", fd));
	write (fd, "0x", 2);
	size = 2;
	if (ptr >= 16)
		size += ft_ptr_util(ptr / 16, fd);
	size += ft_dprint_char(hex[ptr % 16], fd);
	return (size);
}

//lowercase = 1, uppercase = 0
int	ft_dprint_hex(unsigned int nbr, int lower, int fd)
{
	char	*hex;
	int		size;

	size = 0;
	if (lower == 1)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (nbr >= 16)
		size += ft_dprint_hex(nbr / 16, lower, fd);
	size += ft_dprint_char(hex[nbr % 16], fd);
	return (size);
}
