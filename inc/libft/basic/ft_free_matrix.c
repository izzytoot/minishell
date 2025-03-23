/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:41:42 by root              #+#    #+#             */
/*   Updated: 2025/03/23 23:44:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_matrix(void ***matrix)
{
	int	i;
	int	j;

	i = 0;
	if (!matrix || !*matrix)
		return ;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
			free(matrix[i][j++]);
		free(matrix[i++]);
	}
	free(*matrix);
	return ;
}
