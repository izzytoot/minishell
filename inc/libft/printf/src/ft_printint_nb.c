/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:56 by root              #+#    #+#             */
/*   Updated: 2024/11/13 14:17:18 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printint_nb(int n, int fd)
{
	int		r;

	r = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		r = r + ft_printchar ('-', fd);
		n = -n;
	}
	if (n > 9)
		r = r + ft_printint_nb(n / 10, fd);
	r = r + ft_printchar((n % 10) + '0', fd);
	return (r);
}
