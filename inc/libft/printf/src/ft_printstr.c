/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:32:37 by root              #+#    #+#             */
/*   Updated: 2024/11/14 13:03:13 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_printstr("(null)", fd));
	while (str[i])
	{
		ft_printchar(str[i], fd);
		i++;
	}
	return (i);
}
