/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38_token_empties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:44:21 by isabel            #+#    #+#             */
/*   Updated: 2025/05/18 23:03:25 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	empty_case(t_msh **msh, const char *line, int i, bool flag)
{
	t_tk_lst	*empty_tk;
	char		nl[1024];
	int			j;
	int			tmp_i;
	
	j = 0;
	if (!line)
		return;
	while (ft_strchr(WS, line[i]))
		i++;
	tmp_i = i;
	while (line[i])
		nl[j++] = line[i++];
	nl[j] = '\0';
	if (ft_strchr(QT, nl[0]) && (((ch_all_same(nl) || ch_emp_exp(msh, nl))
		&& ((flag || ft_strchr(WS, line[tmp_i - 1]) || !line[i - 1])))
		|| ((ft_strncmp("\"\"", nl, 2) == 0 || ft_strncmp("''", nl, 2) == 0)
		&& (((ft_strchr(WS, line[tmp_i - 1]) && ft_strchr(WS, nl[2]))
		|| (flag && ft_strchr(WS, nl[2])) || (flag && !nl[2]))))))
	{
		empty_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk((*msh), empty_tk, "''", ARG);
	}
	return ;
}

bool ch_emp_exp(t_msh **msh, char *nl)
{
	int	i;
	int	j;
	char kw[2048];
	
	i = 0;
	j = 0;
	while (nl[i] && (ft_strchr(QT, nl[i]) && !ft_strchr(WS, nl[i])))
		i++;
	if (nl[i] != '$')
		return(false);
	while(nl[i] && (!ft_strchr(QT, nl[i]) && !ft_strchr(WS, nl[i])))
	{
		kw[j] = nl[i];
		i++;
		j++;
	}
	kw[j] = '\0';
	if (!get_env_cont((*msh)->envp_list, (*msh)->vars_list, kw))
		return(true);
	return (false);
}

bool ch_all_same(char *nl)
{
	int	i;

	i = 0;
	while (nl[i] && (nl[i + 1] && !ft_strchr(WS, nl[i + 1])))
	{
		if ((nl[i + 1] && (nl[i] != nl[i + 1])) || !ft_strchr(QT, nl[i]))
			return (false);
		i++;
	}
	return (true);
}

int	exp_to_null(t_msh **msh, int start)
{
	int			i;
	char		exp[5];
	t_tk_lst	*new_tk;
	const char *line;
	
	i = start + 1;
	line = (*msh)->prompt_line;
	if (line[i] && !ft_strchr(QT, line[i]))
		return (start);
	while (line[i] && !ft_strchr(WS, line[i]))
	{
		if ((line[i + 1] && (line[i] != line[i + 1])) || !ft_strchr(QT, line[i]))
			return (start);
		i++;
	}
	exp[0] = '\0';	
	new_tk = ft_calloc(1, sizeof(t_tk_lst));
	app_tk(*msh, new_tk, exp, ARG);
	return(i - 1);
}

void	rm_empties(t_tk_lst **curr)
{
	char	*word;

	word = NULL;
	if (!(*curr)->prev || (*curr)->prev->type != ARG)
		return ;
	if ((*curr)->prev->prev && ft_strcmp("\'\'", (*curr)->content) == 0 && (*curr)->prev->content[0] == '$')
	{
		if ((*curr)->next)
		{
			(*curr)->prev->next = (*curr)->next;
			(*curr)->next->prev = (*curr)->prev;
		}
		else
		{
			(*curr)->prev->next = NULL;
			*curr = (*curr)->prev;
		}
		return ;
	}
	if ((*curr)->prev->type == ARG)
		word = ft_strdup((*curr)->prev->content);
	if (ft_strcmp("\'\'", word) == 0 && ((*curr)->type == BT_CMD || (*curr)->type == ARG))
	{
		if ((*curr)->prev->type == ARG && (*curr)->prev->prev)
		{
			(*curr)->prev->prev->next = *curr;
			(*curr)->prev = (*curr)->prev->prev;
		}
		else if ((*curr)->prev->type == ARG && !(*curr)->prev->prev)
			(*curr)->prev = NULL;
	}
	safe_free(word);
}
