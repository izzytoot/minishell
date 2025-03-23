/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:42:37 by root              #+#    #+#             */
/*   Updated: 2025/03/23 23:44:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_error_msg(char *message, char *complete, int if_exit)
{
	if (complete == NULL)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
		if (if_exit == 1)
			exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd(complete, 2);
		ft_putstr_fd("\n", 2);
		if (if_exit == 1)
			exit(EXIT_FAILURE);
	}
}