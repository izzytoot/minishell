/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:27:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/28 10:37:35 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_list_to_array(char ***str, t_list **list)
{
	t_list	*current_node;
	int		size;
	int		i;

	size = ft_lstsize(*list);
	*str = malloc(sizeof(char *) * (size + 1));
	if (!*str)
		return ;
	current_node = *list;
	i = 0;
	while (current_node && i < size)
	{
		(*str)[i] = ft_strdup(current_node->content);
		current_node = current_node->next;
		i++;
	}
	(*str)[i] = NULL;
	return ;
}
