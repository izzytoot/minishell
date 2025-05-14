/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38_token_empties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:44:21 by isabel            #+#    #+#             */
/*   Updated: 2025/05/14 15:42:23 by isabel           ###   ########.fr       */
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
	{
		nl[j++] = line[i];
		i++;
	}
	nl[j] = '\0';
	if ((ft_strncmp("\"\"", nl, 2) == 0|| ft_strncmp("''", nl, 2) == 0) && 
		((ft_strchr(WS, line[tmp_i - 1]) && ft_strchr(WS, nl[2]))
		|| (flag && ft_strchr(WS, nl[2])) || (flag && !nl[2])))
	{
		empty_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk((*msh), empty_tk, "''", ARG);	
	}
	return ;
}

void	rm_empties(t_tk_lst **curr)
{
	char	*word;

	if (!(*curr)->prev || (*curr)->prev->type != ARG)
		return ;
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