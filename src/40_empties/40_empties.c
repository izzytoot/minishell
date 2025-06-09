/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   40_empties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:44:21 by isabel            #+#    #+#             */
/*   Updated: 2025/06/09 19:30:44 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	empty_case(t_msh **msh, const char *line, int i, bool fl)
{
	t_tk_lst	*empty_tk;
	char		nl[1024];
	int			tmp_i;

	i = sp_for_empty_case (msh, line, i, 2);
	tmp_i = i;
	rest_of_word(nl, line, i);
	if (!nl[0])
		return (tmp_i);
	if (ft_strchr(QT, nl[0]) && (((ch_all_same(nl) || ch_emp_exp(msh, nl))
				&& ((fl || ((tmp_i > 0 && ft_strchr(WS, line[tmp_i - 1])))
						|| (i == 0 || !line[i - 1])))) || emp_1(nl, line, tmp_i)
			|| emp_2(nl, fl)))
	{
		if (ch_emp_exp(msh, nl))
			tmp_i = (tmp_i + ch_emp_exp(msh, nl));
		if (ch_all_same(nl))
			tmp_i = (tmp_i + ch_all_same(nl));
		empty_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk((*msh), empty_tk, "''", ARG);
	}
	return (tmp_i);
}

int	ch_empty_case(t_msh **msh, const char *line, int i, bool fl)
{
	char		nl[1024];
	int			j;
	int			tmp_i;

	if (sp_for_empty_case(msh, line, i, 1))
		return (0);
	i = sp_for_empty_case(msh, line, i, 2);
	tmp_i = i;
	j = 0;
	while (line[i])
		nl[j++] = line[i++];
	nl[j] = '\0';
	if (!nl[0])
		return (tmp_i);
	if (ft_strchr(QT, nl[0]) && (((ch_all_same(nl) || ch_emp_exp(msh, nl))
				&& ((fl || ((tmp_i > 0 && ft_strchr(WS, line[tmp_i - 1])))
						|| (i == 0 || !line[i - 1])))) || emp_1(nl, line, tmp_i)
			|| emp_2(nl, fl)))
		return (1);
	return (0);
}

int	sp_for_empty_case(t_msh **msh, const char *line, int i, int n)
{
	int	j;

	if (n == 1)
	{
		j = -1;
		while (line[++j])
		{
			if (!ft_strchr(WS, line[j]))
				break ;
		}
		if (line[j] == '\0')
			return (1);
		return (0);
	}
	if (n == 2)
	{
		if (line[i] && ft_strchr(WS, line[i]))
			i = tk_space(msh, i);
		while (line[i] && ft_strchr(WS, line[i]))
			i++;
	}
	return (i);
}

int	ch_emp_exp(t_msh **msh, char *nl)
{
	int		i;
	int		j;
	char	kw[2048];

	i = 0;
	j = 0;
	while (nl[i] && (nl[i] == '\"') && !ft_strchr(WS, nl[i]))
		i++;
	if (nl[i] != '$')
		return (0);
	i++;
	if (ft_strchr(QT, nl[i]) || ft_strchr(WS, nl[i]))
		return (0);
	while (nl[i] && (!ft_strchr(QT, nl[i]) && !ft_strchr(WS, nl[i])
			&& !ft_strchr(SYM_EXP, nl[i])))
	{
		kw[j] = nl[i];
		i++;
		j++;
	}
	kw[j] = '\0';
	if (!ch_env_cont((*msh)->envp_list, (*msh)->vars_list, kw))
		return (i++);
	return (0);
}

int	ch_all_same(char *nl)
{
	int	i;

	i = 0;
	while (nl[i] && (nl[i + 1] && !ft_strchr(WS, nl[i + 1])
			&& !ft_strchr("|", nl[i + 1])))
	{
		if ((nl[i + 1] && (nl[i] != nl[i + 1])) || !ft_strchr(QT, nl[i]))
			return (0);
		i++;
	}
	if (!nl[i + 1] || (nl[i + 1] && (ft_strchr(WS, nl[i + 1])
				|| ft_strchr("|", nl[i + 1]))))
		return (i);
	return (0);
}
