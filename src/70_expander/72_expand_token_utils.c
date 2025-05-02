/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   72_expand_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:17 by isabel            #+#    #+#             */
/*   Updated: 2025/05/02 11:43:30 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_exp(char *arg, int i)
{
	int	count;
	
	count = 0;
	while(arg[i] && !ft_strchr(WHITESPACE, arg[i]))
	{
		if (arg[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*kw_array_util(char *arg, int *k, int **i, int n)
{
	if (!n)
		return (NULL);
	if (n == 1)
	{
		(**i)++;
		return (ft_strdup("$"));
	}
	if (n == 2)
		return (get_key_word(arg, *i));
	else
	{
		(void)*k;
		return (get_mid_cont(arg, *i));
	}
}

int	count_kw(char **kw, bool *flag)
{
	int	k;
	int	count;
	
	k = 0;
	count = 0;
	while(kw[k])
	{
		if (kw[k][0] == '$' && !kw[k][1])
			*flag = true;
		count++;
		k++;
	}
	return (count);
}

void	subst_arg(char **arg, char *pre_c, char *new_c, char *post_c)
{
	char	*final_content;
	
	if (new_c)
	{
		final_content = get_final_cont(new_c, pre_c, post_c);
		free(*arg);
		*arg = ft_strdup(final_content);
	}
	else if(pre_c || post_c)
	{	
		if (pre_c)
			final_content = ft_strdup(pre_c);
		if (post_c)
			final_content = ft_strjoin(final_content, ft_strdup(post_c));
		free(*arg);
		*arg = ft_strdup(final_content);
	}
	else
		*arg = NULL;
}

void	subst_fname(char **fname, char *pre_c, char *new_c, char *post_c)
{
	char	*final_content;
	
	if (new_c)
	{
		final_content = get_final_cont(new_c, pre_c, post_c);
		*fname = ft_strdup(final_content);
	}
	else if(pre_c || post_c)
	{	
		if (pre_c)
			final_content = ft_strdup(pre_c);
		if (post_c)
			final_content = ft_strjoin(final_content, ft_strdup(post_c));
		*fname = ft_strdup(final_content);
	}
	else
		*fname = NULL;
}
