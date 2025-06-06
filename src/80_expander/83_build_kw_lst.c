/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   83_build_kw_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:26:34 by isabel            #+#    #+#             */
/*   Updated: 2025/06/06 17:43:01 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	build_kw_list(t_kw **kw_lst, char *arg, int *i)
{
	t_kw	*n_kw;
	int		count;
	char	next;

	count = count_exp(arg, *i);
	while (arg[*i] && !ft_strchr(WS, arg[*i])
		&& !ft_strchr(SYM_EXP, arg[*i]) && !ft_strchr(QT, arg[*i]))
	{
		while (count-- > 0)
		{
			if (*i < (int)ft_strlen(arg))
				next = arg[*i + 1];
			else
				next = '\0';
			n_kw = ft_calloc(1, sizeof(t_kw));
			get_exp_kw(next, n_kw, arg, i);
			app_kw(kw_lst, n_kw, n_kw->kw, true);
			if (arg[*i] && check_mid(arg[*i]))
			{
				n_kw = ft_calloc(1, sizeof(t_kw));
				n_kw->kw = get_util(arg, &i, 4);
				app_kw(kw_lst, n_kw, n_kw->kw, false);
			}
		}
	}
}

void	get_exp_kw(int next, t_kw *n_kw, char *arg, int *i)
{
	if (arg[*i] == '$' && (!next || ft_strchr(WS, next) || ft_strchr(QT, next)
			|| (ft_isdigit(next) || (ft_strchr(SYM_EXP, next) && next != '?')
				|| next == '$')))
	{
		if (ft_isdigit(next) || next == '?' || next == '$')
			n_kw->kw = get_util(arg, &i, 5);
		else
			n_kw->kw = get_util(arg, &i, 1);
		(*i)++;
	}
	else
	{
		if (arg[*i] == '$' && next)
			n_kw->kw = get_util(arg, &i, 2);
	}
}

char	*get_util(char *arg, int **i, int n)
{
	if (!n)
		return (NULL);
	if (n == 1)
		return (ft_strdup("$"));
	if (n == 2)
		return (get_key_word(arg, *i));
	if (n == 4)
		return (get_mid_cont_w_sp(arg, *i));
	if (n == 5)
	{
		(**i)++;
		if (arg[**i] == '?')
			return (ft_strdup("?"));
		if (arg[**i] == '$')
			return (ft_strdup("$$"));
		else if (arg[**i] == '0')
			return (ft_strdup("0"));
		else if (ft_isdigit(arg[**i]))
			return (ft_char_to_str(arg[**i]));
	}
	else
		return (get_mid_cont(arg, *i));
	return (NULL);
}

void	app_kw(t_kw **kw_lst, t_kw *new_kw, char *kw, bool exp)
{
	t_kw	*tmp;

	tmp = *kw_lst;
	new_kw->kw = ft_strdup(kw);
	kw = safe_free(kw);
	new_kw->exp = exp;
	new_kw->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		new_kw->prev = tmp;
		tmp->next = new_kw;
	}
	else
	{
		*kw_lst = new_kw;
		new_kw->prev = NULL;
	}
}

bool	check_dollar_w_qts(char **str)
{
	int		i;
	char	c;
	char	*str_tmp;

	i = 0;
	while ((*str)[i])
	{
		c = (*str)[i];
		i++;
	}
	if (c == '$')
	{
		str_tmp = (*str);
		(*str) = ft_strdup_until((*str), c);
		str_tmp = safe_free(str_tmp);
		return (true);
	}
	return (false);
}
