/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:57:55 by root              #+#    #+#             */
/*   Updated: 2025/01/23 15:49:36 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_print_format(char spec, va_list ap, int fd)
{
	int	r;

	r = 0;
	if (spec == 'c')
		r = ft_printchar(va_arg(ap, int), fd);
	else if (spec == 's')
		r = ft_printstr(va_arg(ap, char *), fd);
	else if (spec == 'p')
		r = ft_printptr((unsigned long)va_arg(ap, unsigned long), fd);
	else if (spec == 'd' || spec == 'i')
		r = ft_printint_nb(va_arg(ap, int), fd);
	else if (spec == 'u')
		r = ft_printint_u(va_arg(ap, unsigned int), fd);
	else if (spec == 'x' || spec == 'X')
		r = ft_printint_hex(spec, va_arg(ap, unsigned int), fd);
	else
		r += write(fd, &spec, 1);
	return (r);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	unsigned int	r;
	int				fd;

	va_start(ap, format);
	r = 0;
	fd = 1;
	while (*format)
	{
		if (*format == '%')
			r = r + ft_print_format(*(++format), ap, fd);
		else
			r = r + ft_printchar(*format, fd);
		if (*format == 0)
		{
			return (-1);
			break ;
		}
		++format;
	}
	va_end(ap);
	return (r);
}
