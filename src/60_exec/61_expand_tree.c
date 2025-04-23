/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   61_expand_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:01:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/23 17:52:44 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	expand_tree(t_msh **msh, t_tree_nd *node)
{
	int	i;
	int	j;

	i = 0;
	if (!node)
		return ;
	if (type_is_cmd(&node->type) || node->type == ARG)
	{
		if (node->args)
		{
			while (node->args[i])
			{
				j = -1;
				if (node->quote_lst->in_squotes)
				{
					node->quote_lst = node->quote_lst->next;
					i++;
				}
				else
				{
					if (node->args[i][++j] == '$')
						expand_tk(msh, &node->args[i]);
				}
				if (!node->quote_lst->next)
					break ;
				node->quote_lst = node->quote_lst->next;
				i++;
			}
		}
	}
	if (node->left)
		expand_tree(msh, node->left);
	if(node->right)
		expand_tree(msh, node->right);
}

void	handle_qt_exp(t_msh **msh, t_tree_nd *node)
{
	int	i;
	int	j;
	
	i = 0;
	while (node->args[i])
	{
		j = -1;
		while(node->quote_lst->content)
		{
			if (strcmp(node->args[i], node->quote_lst->content) == 0)
			{
				if (node->quote_lst->in_dquotes)
				{
					if (node->args[i][++j] == '$')
						expand_tk(msh, &node->args[i]);
				}
				else if(node->quote_lst->in_squotes)
					break ;
			}
			node->quote_lst = node->quote_lst->next;
		}
		i++;
	}
}


// void	expand_tree(t_msh **msh, t_tree_nd *node)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!node)
// 		return ;
// 	if (type_is_cmd(&node->type) || node->type == ARG)
// 	{
// 		if (node->args && !node->quote_lst)
// 		{
// 			while (node->args[i])
// 			{
// 				j = -1;
// 				if (node->args[i][++j] == '$')
// 					expand_tk(msh, &node->args[i]);
// 				i++;
// 			}
// 		}
// 		else if (node->args && node->quote_lst)
// 			handle_qt_exp(msh, node);
// 	}
// 	if (node->left)
// 		expand_tree(msh, node->left);
// 	if(node->right)
// 		expand_tree(msh, node->right);
// }

// void	handle_qt_exp(t_msh **msh, t_tree_nd *node)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	while (node->args[i])
// 	{
// 		j = -1;
// 		while(node->quote_lst->content)
// 		{
// 			if (strcmp(node->args[i], node->quote_lst->content) == 0)
// 			{
// 				if (node->quote_lst->in_dquotes)
// 				{
// 					if (node->args[i][++j] == '$')
// 						expand_tk(msh, &node->args[i]);
// 				}
// 				else if(node->quote_lst->in_squotes)
// 					break ;
// 			}
// 			node->quote_lst = node->quote_lst->next;
// 		}
// 		i++;
// 	}
// }

void	expand_tk(t_msh **msh, char **args)
{
	char	*key_word;
	char	*new_content;
	char	*final_content;
	int		len;
	
	key_word = ft_strdup(&(*args)[1]);
	if (ft_strcmp(key_word, "0") == 0)
		new_content = ft_strdup("minishell");
	else if(ft_strcmp(key_word, "?") == 0)
		new_content = ft_strdup(ft_itoa(exit_value(msh, 0, 0, 0)));
	else
		new_content = get_env_content((*msh)->envp_list, key_word);
	if (new_content)
	{
		len = ft_strlen(new_content);
		if (len > 0 && new_content[len - 1] == '\n')
			final_content = ft_substr(new_content, 0, len - 1);
		else
			final_content = ft_strdup(new_content);
		free(*args);
		*args = ft_strdup(final_content);
		free(final_content);
	}
	free(key_word);
}

char *get_env_content(t_list *envp_list, char *key_word)
{
	int	key_len;

	key_len = ft_strlen(key_word);
	while(envp_list)
	{
		if (!ft_strncmp(envp_list->content, key_word, key_len)
				&& ((char *)envp_list->content)[key_len] == '=')
			return(&((char *)envp_list->content)[key_len + 1]);
		envp_list = envp_list->next;
	}
	return (NULL);
}