/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38_token_empties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:44:21 by isabel            #+#    #+#             */
/*   Updated: 2025/05/23 19:28:03 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	empty_case(t_msh **msh, const char *line, int i, bool fl)
{
	t_tk_lst	*empty_tk;
	char		nl[1024];
	int			j;
	int			tmp_i;

	if (!line[i])
		return (i);
	i = sp_for_empty_case (msh, line, i);
	tmp_i = i;
	j = 0;
	while (line[i])
		nl[j++] = line[i++];
	nl[j] = '\0';
	if (!nl[0])
		return (tmp_i);
	if (ft_strchr(QT, nl[0]) && (((ch_all_same(nl) || ch_emp_exp(msh, nl))
				&& ((fl || ft_strchr(WS, line[tmp_i - 1]) || !line[i - 1])))
			|| ((ft_strncmp("\"\"", nl, 2) == 0 || ft_strncmp("''", nl, 2) == 0)
				&& (((ft_strchr(WS, line[tmp_i - 1]) && ft_strchr(WS, nl[2]))
						|| (fl && ft_strchr(WS, nl[2])) || (fl && !nl[2]))))))
	{
		empty_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk((*msh), empty_tk, "''", ARG);
	}
	return (tmp_i);
}

int	sp_for_empty_case(t_msh **msh, const char *line, int i)
{
	if (line[i] && ft_strchr(WS, line[i]))
		i = tk_space(msh, i);
	while (line[i] && ft_strchr(WS, line[i]))
		i++;
	return (i);
}

bool	ch_emp_exp(t_msh **msh, char *nl)
{
	int		i;
	int		j;
	char	kw[2048];

	i = 0;
	j = 0;
	while (nl[i] && (ft_strchr(QT, nl[i]) && !ft_strchr(WS, nl[i])))
		i++;
	if (nl[i] != '$')
		return (false);
	i++;
	if (ft_strchr(QT, nl[i]))
		return (false);
	while (nl[i] && (!ft_strchr(QT, nl[i]) && !ft_strchr(WS, nl[i])))
	{
		kw[j] = nl[i];
		i++;
		j++;
	}
	kw[j] = '\0';
	if (!get_env_cont((*msh)->envp_list, (*msh)->vars_list, kw))
		return (true);
	return (false);
}

bool	ch_all_same(char *nl)
{
	int	i;

	i = 0;
	while (nl[i] && (nl[i + 1] && !ft_strchr(WS, nl[i + 1])))
	{
		if ((nl[i + 1] && (nl[i] != nl[i + 1])) || !ft_strchr(QT, nl[i]))
			return (false);
		i++;
	}
	if (!nl[i + 1])
		return (true);
	return (false);
}
