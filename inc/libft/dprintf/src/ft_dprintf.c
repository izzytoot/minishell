/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:53:42 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/04 11:53:42 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_dprintf.h"

//info    --> Produce output according to a format
//fd      --> Fd to write the output to
//format  --> Str that specifies how args are converted for output
//return  --> Success (Number of bytes printed, except '\0')

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		size;
	int		i;

	va_start(args, format);
	size = 0;
	i = 0;
	if (!format || fd < 0)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			size += ft_dprint_args(args, format[i + 1], fd);
			i++;
		}
		else
			size += ft_dprint_char(format[i], fd);
		i++;
	}
	va_end(args);
	return (size);
}

int	ft_dprint_args(va_list args, char letter, int fd)
{
	if (letter == 'c')
		return (ft_dprint_char(va_arg(args, int), fd));
	if (letter == 's')
		return (ft_dprint_str(va_arg(args, char *), fd));
	if (letter == 'p')
		return (ft_dprint_ptr(va_arg(args, unsigned long), fd));
	if (letter == 'd' || letter == 'i')
		return (ft_dprint_int(va_arg(args, int), fd));
	if (letter == 'u')
		return (ft_dprint_unsign(va_arg(args, unsigned int), fd));
	if (letter == 'x')
		return (ft_dprint_hex(va_arg(args, unsigned int), 1, fd));
	if (letter == 'X')
		return (ft_dprint_hex(va_arg(args, unsigned int), 0, fd));
	if (letter == '%')
		return (ft_dprint_char('%', fd));
	return (0);
}
