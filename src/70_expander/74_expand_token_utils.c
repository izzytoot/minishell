/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   74_expand_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:17 by isabel            #+#    #+#             */
/*   Updated: 2025/05/10 02:27:03 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (n == 4)
	{
		(void)*k;
		return (get_mid_cont_w_sp(arg, *i));
	}
	else
	{
		(void)*k;
		return (get_mid_cont(arg, *i));
	}
}

void	check_kw_flag(char *prev_kw, char *kw, bool *flag)
{
	if (kw[0] == '$' && !kw[1])
		*flag = true;
	if (prev_kw)
	{
		if (ft_strcmp(prev_kw, "?") == 0)
			*flag = true;
	}
	else
		*flag = false;
}

int	count_exp(char *arg, int i)
{
	int	count;
	
	count = 0;
	while(arg[i])
	{
		if (arg[i] == '$')
			count++;
		i++;
	}	
	return (count);
}

int	count_kw(char **kw)
{
	int	k;
	int	count;
	
	k = 0;
	count = 0;
	while(kw[k])
	{
		count++;
		k++;
	}
	return (count);
}
