/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:36:26 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/31 12:42:37 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_node *new_tree_node(t_token_type *type, char *content)
{
	t_tree_node *new_node;

	new_node = ft_calloc(1, sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	new_node->type = *type;
	new_node->args = NULL;
	new_node->content = content;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->straight = NULL;
	new_node->fd = 0;
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

char	**ft_arraydup(char **array)
{
    int 	i;
	int 	size;
    char	**new_array;

    if (!array)
        return (NULL);
    size = 0;
    while (array[size])
        size++;
    new_array = malloc(sizeof(char *) * (size + 1));
    if (!new_array)
        return (NULL);
    i = -1;
    while (++i < size)
    {
        new_array[i] = ft_strdup(array[i]);
        if (!new_array[i])
		{
			ft_free_arrays((void**)new_array);
			return (NULL);
		}
    }
    new_array[size] = NULL;
    return (new_array);
}

bool	tk_is_redir(t_token_type *type)
{
	if (*type == REDIR_APP || *type == REDIR_HD || *type == REDIR_IN || *type == REDIR_OUT)
		return(true);
	else
		return (false);
}

bool	tk_is_cmd(t_token_type *type)
{
	if (*type == WORD || *type ==  ARG || *type == BT_CMD || *type == ENV_CMD)
		return(true);
	else
		return (false);
}