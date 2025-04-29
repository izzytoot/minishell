/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   62_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:41:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/24 18:27:21 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	recurs_exp_tree(t_msh **msh, t_tree_nd *node)
{
	if (node->left)
		expand_tree(msh, node->left);
	if(node->right)
		expand_tree(msh, node->right);
}

char *get_env_cont(t_list *envp_list, char *key_word)
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

char	*get_pre_cont(char *arg, int *i)
{
	char	*pre_content;
	int		len;
	
	len = 0;
	while(!ft_strchr("$",arg[++*i]))
		len++;
	if (!len)
		return (NULL);
	pre_content = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = -1;
	while(!ft_strchr("$",arg[++*i]))
	{
		pre_content[len] = arg[len];
		len++;
	}
	pre_content[len] = '\0';
	return(pre_content);
}

char	*get_key_word(char *arg, int *i)
{
	char	*key_word;
	int		len;
	int		tmp_i;
	
	len = 0;
	tmp_i = *i;
	while(!ft_strchr(WHITESPACE,arg[(*i)++]))
	{
		if(arg[*i] == '$')
			break;
		len++;
	}
	if (!len)
		return (NULL);
	key_word = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = tmp_i;
	while(!ft_strchr(WHITESPACE,arg[(*i)++]))
	{
		if(arg[*i] == '$')
			break;
		key_word[len] = arg[*i];
		len++;
	}
	key_word[len] = '\0';
	return(key_word);
}

char	*get_post_cont(char *arg, int *i)
{
	char	*post_content;
	int		len;
	int		tmp_i;
	
	len = 0;
	tmp_i = *i;
	while(arg[++(*i)])
		len++;
	if (len == 0)
		return (NULL);
	post_content = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = tmp_i;
	while(arg[*i])
	{
		post_content[len] = arg[*i];
		len++;
		(*i)++;
	}
	post_content[len] = '\0';
	return(post_content);
}

