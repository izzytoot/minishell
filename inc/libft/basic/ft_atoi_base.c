/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:45:31 by root              #+#    #+#             */
/*   Updated: 2025/04/04 12:51:37 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_digit(char c, int base);

int	ft_atoi_base(const char *str, int base)
{
	int	i;
	int	neg;
	int	nbr;
	int	digit;

	i = 0;
	neg = 1;
	nbr = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i])
	{
		digit = get_digit(str[i], base);
		if (digit == -1)
			break ;
		nbr = (nbr * base) + digit;
		i++;
	}
	return (nbr * neg);
}

static int	get_digit(char c, int base)
{
	int	digit;

	if (c >= '0' && c <= '9')
		digit = c - '0';
	else if (c >= 'A' && c <= 'F')
		digit = c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		digit = c - 'a' + 10;
	else
		return (-1);
	if (digit >= base)
		return (-1);
	return (digit);
}
