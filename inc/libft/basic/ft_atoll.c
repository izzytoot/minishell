/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:58:50 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/21 14:01:15 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//info   --> Convert a str to a long long
//nptr   --> String to convert
//return --> Success (int)
//return --> Failure (0)

static long long	check_overflow(long long nbr, char nptr, int neg);

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			neg;
	long long	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nbr = check_overflow(nbr, nptr[i], neg);
		if (nbr == LLONG_MAX || nbr == LLONG_MIN)
			return (nbr);
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nbr * neg);
}

//info --> checks for overflow and it returns the correct values accordingly

static long long	check_overflow(long long nbr, char nptr, int neg)
{
	int	digit;

	digit = nptr - '0';
	if (neg == 1 && (nbr > LLONG_MAX / 10
			|| (nbr == LLONG_MAX / 10 && digit > LLONG_MAX % 10)))
		return (LLONG_MAX);
	if (neg == -1 && (nbr > LLONG_MAX / 10
			|| (nbr == LLONG_MAX / 10 && digit > (LLONG_MAX % 10) + 1)))
		return (LLONG_MIN);
	return (nbr);
}
