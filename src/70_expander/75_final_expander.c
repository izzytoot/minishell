/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   75_final_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:53:13 by isabel            #+#    #+#             */
/*   Updated: 2025/05/09 12:55:42 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_env_cont(t_list *envp_list, t_list *vars_list, char *key_word)
{
	int		key_len;

	key_len = ft_strlen(key_word);
	while (envp_list)
	{
		if (!ft_strncmp(envp_list->content, key_word, key_len)
				&& ((char *)envp_list->content)[key_len] == '=')
			return(&((char *)envp_list->content)[key_len + 1]);
		envp_list = envp_list->next;
	}
	while (vars_list)
	{
		if (!ft_strncmp(vars_list->content, key_word, key_len)
			&& ((char *)vars_list->content)[key_len] == '=')
			return(&((char *)vars_list->content)[key_len + 1]);
		vars_list = vars_list->next;
	}
	return (NULL);
}

char	*get_final_cont(char *new_c, char *pre_c, char *post_c)
{
	char	*final_content;
	int		len;
	char	*tmp;
	char	*new_tmp;
	
	len = ft_strlen(new_c);
	if (len > 0 && new_c[len - 1] == '\n')
	{
		tmp = get_tmp(new_c, post_c, len);
		final_content = ultimate_joint(pre_c, tmp);
	}
	else
	{
		tmp = new_c;
		//tmp = ft_strdup(new_c);
		if (pre_c)
			final_content = ft_strjoin(pre_c, tmp);
		else
			final_content = tmp;
			//final_content = ft_strdup(tmp);
		if (post_c)
		{
			new_tmp = get_new_tmp(tmp, final_content);
			final_content = ft_strjoin(new_tmp, post_c);
		}
	}
	return(final_content);	
}

char	*get_tmp(char *new_c, char *post_c, int len)
{
	char	*tmp;
	
	if (post_c)			
		tmp = ft_strjoin(ft_substr(new_c, 0, len - 1), post_c);
	else
		tmp = ft_substr(new_c, 0, len - 1);
	return (tmp);
}

char	*ultimate_joint(char *pre_c, char *tmp)
{
	char	*final_content;
	
	if (pre_c)
		final_content = ft_strjoin(pre_c, tmp);
	else
		final_content = tmp;
		//final_content = ft_strdup(tmp);
	return (final_content);
}

char	*get_new_tmp(char *tmp, char *f_c)
{
	char	*new_tmp;
	
	free(tmp);
	new_tmp = ft_calloc((ft_strlen(f_c) + 1), sizeof(char));
	new_tmp = f_c;
	//new_tmp = ft_strdup(f_c);
	return (new_tmp);
}
