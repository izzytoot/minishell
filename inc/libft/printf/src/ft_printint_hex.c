/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:27:53 by icunha-t          #+#    #+#             */
/*   Updated: 2024/11/13 17:35:16 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printint_hex(char spec, unsigned int n, int fd)
{
	int		r;
	char	*hexa;

	r = 0;
	if (spec == 'X')
		hexa = HEX_UPP;
	else
		hexa = HEX_LOW;
	if (n >= 16)
	{
		r = r + ft_printint_hex(spec, n / 16, fd);
		r = r + ft_printint_hex(spec, n % 16, fd);
	}
	else
		r = r + ft_printchar (hexa[n], fd);
	return (r);
}
