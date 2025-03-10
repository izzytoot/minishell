/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:56:29 by icunha-t          #+#    #+#             */
/*   Updated: 2024/11/13 17:51:23 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printint_u(unsigned int n, int fd)
{
	unsigned int		r;

	r = 0;
	if (n > 9)
		r = r + ft_printint_u(n / 10, fd);
	r = r + ft_printchar((n % 10) + '0', fd);
	return (r);
}
