/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   72_expand_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:17 by isabel            #+#    #+#             */
/*   Updated: 2025/05/01 15:19:00 by isabel           ###   ########.fr       */
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
