/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:36:26 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/25 12:06:13 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_node *new_tree_node(t_token_type *type, t_tree_node *left, t_tree_node *right)
{
	t_tree_node *new_node;

	new_node = ft_calloc(1, sizeof(t_tree_node));
	new_node->type = *type;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

char **conv_list_to_array(t_list *list)
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
	while(i < size)
	{
		array[i] = ft_strdup(current_node->content);
		current_node = list->next;
	}
	array[i] = NULL;
	return (array);
}