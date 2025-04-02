/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:48:18 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/02 18:48:38 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_init_var(void **var1, void **var2, void **var3, void **var4)
{
	if (var1)
		*var1 = NULL;
	if (var2)
		*var2 = NULL;
	if (var3)
		*var3 = NULL;
	if (var4)
		*var4 = NULL;
}

