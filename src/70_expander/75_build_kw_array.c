/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   75_build_kw_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:26:34 by isabel            #+#    #+#             */
/*   Updated: 2025/05/10 19:33:56 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**build_kw_array(char *arg, int *i)
{
	char	**kw;
	int		tmp;
	t_ints	ints;
	char	c;
	kw = ft_calloc(MAX_KW, sizeof(char *));
	init_kw_vars(&tmp, &i, &ints, arg);
	while(arg[*i] && !ft_strchr(WS, arg[*i])
		&& !ft_strchr(SYM_EXP, arg[*i]) && !ft_strchr(QT, arg[*i]))
	{	
		c = arg[*i + 1];
		if (arg[*i] == '$' && (!c || ft_strchr(WS, c)
			|| (ft_isdigit(c) || (ft_strchr(SYM_EXP, c) && c != '?'))))
		{
			if (!sp_cases(kw, arg, &ints, &i))
				return (free_kw_error(kw));
		}
		while(ints.j > 0)
		{
			if (!build_rest(kw, arg, &ints, &i))
				return (free_kw_error(kw));
			ints.j--;
		}
		if (arg[*i])
			ints.i++;
	}
	kw[ints.i] = NULL;
	return (kw);
}

void	init_kw_vars(int *tmp, int **i, t_ints *ints, char *arg)
{
	*tmp = **i;
	ints->j = count_exp(arg, *tmp);
	ints->i = 0;
}

int	sp_cases(char **kw, char *arg, t_ints *ints, int **i)
{	
	if (ints->i >= MAX_KW - 1)
		return (0);
	if (ft_isdigit(arg[**i + 1]) || arg[**i + 1] == '?')
		kw[ints->i] = kw_array_util(arg, &ints->i, i, 5);
	else
		kw[ints->i] = kw_array_util(arg, &ints->i, i, 1);
	ints->i++;
	(**i)++;
	return (1);
}

int	build_rest(char **kw, char *arg, t_ints *ints, int **i)
{
	if (ints->i >= MAX_KW - 1)
		return (0);
	if (arg[**i] == '$' && arg[**i + 1])
	{
		kw[ints->i] = kw_array_util(arg, &ints->i, i, 2);
		ints->i++;
	}
	if (arg[**i] && check_mid(arg[**i]))
	{
		if (ints->j - 1 == 0)
			kw[ints->i] = kw_array_util(arg, &ints->i, i, 3);
		else
			kw[ints->i] = kw_array_util(arg, &ints->i, i, 4);
		ints->i++;	
	}
	return (1);
}
