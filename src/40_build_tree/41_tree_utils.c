/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:36:26 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/01 18:33:25 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree_node *new_tree_node(t_token_type *type, char *content)
{
	t_tree_node *new_node;

	new_node = ft_calloc(1, sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->type = *type;
	new_node->args = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->straight = NULL;
	new_node->fd = 0;
	return (new_node);
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
/*
t_tree_node *attach_redir(t_tree_node *redir_node, t_tree_node *new_redir)
{
    if (!redir_node) 
        return (new_redir);
    redir_node->left = new_redir;
    return (redir_node);
}
*/

t_tree_node *attach_redir(t_tree_node *redir_node, t_tree_node *new_redir)
{
    if (!redir_node) 
        return (new_redir);
	else
		redir_node->left = attach_redir(redir_node->left, new_redir);
    return (redir_node);
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
