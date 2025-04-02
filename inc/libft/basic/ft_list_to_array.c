/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:27:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/01 16:28:59 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char **ft_list_to_array(t_list *list)
{
	char 	**array;
	t_list *current_node;
	int		size;
	int		i;
	
	size = ft_lstsize(list);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	current_node = list;
	i = 0;
	while(current_node && i < size)
	{
		array[i] = ft_strdup(current_node->content);
		current_node = current_node->next;
		i++;
	}
	array[i] = NULL;
	i = 0;
	ft_lstclear(&list, free);
	return (array);
}