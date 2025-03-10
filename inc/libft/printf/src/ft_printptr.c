/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:40:49 by root              #+#    #+#             */
/*   Updated: 2024/11/14 13:08:07 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_printhex(unsigned long n, int fd)
{
	char	*sym;

	sym = HEX_LOW;
	if (n < 16)
		ft_printchar(sym[n], fd);
	else
	{
		ft_printhex(n / 16, fd);
		ft_printchar(sym[n % 16], fd);
	}
}

static int	ft_hexlen(unsigned long n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 16;
		++i;
	}
	return (i);
}

int	ft_printptr(unsigned long n, int fd)
{
	if (!n)
		return (ft_printstr("(nil)", fd));
	ft_printstr("0x", fd);
	ft_printhex(n, fd);
	return (ft_hexlen(n) + 2);
}
