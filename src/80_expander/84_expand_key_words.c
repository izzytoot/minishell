/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   84_expand_key_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:48:17 by isabel            #+#    #+#             */
/*   Updated: 2025/06/07 00:07:24 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_kw(t_msh **msh, t_kw **kw_lst)
{
	t_kw	*curr_kw;

	curr_kw = *kw_lst;
	while (curr_kw)
	{
		if (expand_case(curr_kw->kw) == 1 || expand_case(curr_kw->kw) == 4
			|| (expand_case(curr_kw->kw) == 5 && !(*kw_lst)->next))
			;
		else if (other_expand_cases(msh, &curr_kw->kw))
			;
		else if (expand_case(curr_kw->kw) == 7)
		{
			if (curr_kw->exp)
				curr_kw->kw = get_env_cont((*msh)->envp_list, (*msh)->vars_list,
						curr_kw->kw);
		}
		curr_kw = curr_kw->next;
	}
}

int	expand_case(char *kw)
{
	if (!kw || !kw[0])
		return (1);
	if (ft_strcmp(kw, "0") == 0)
		return (2);
	else if (ft_strcmp(kw, "?") == 0)
		return (3);
	else if (ft_strchr(SYM_EXP, kw[0]) || ft_strchr(WS, kw[0]))
		return (4);
	else if (ft_strcmp(kw, "$") == 0)
		return (5);
	else if (ft_strcmp(kw, "$$") == 0)
		return (6);
	return (7);
}

bool	other_expand_cases(t_msh **msh, char **kw)
{
	if (expand_case(*kw) == 6)
	{
		*kw = safe_free(*kw);
		*kw = ft_strdup(ERR_PID_EXP);
		return (true);
	}
	else if (expand_case(*kw) == 2)
	{
		*kw = safe_free(*kw);
		*kw = ft_strdup("minishell");
		return (true);
	}
	else if (expand_case(*kw) == 3)
	{
		*kw = safe_free(*kw);
		*kw = ft_itoa(exit_value(msh, 0, 0, 0));
		return (true);
	}
	return (false);
}

char	*get_env_cont(t_list *envp_list, t_list *vars_list, char *key_word)
{
	int		key_len;
	char	*res;

	key_len = ft_strlen(key_word);
	res = find_env_value(envp_list, key_word, key_len);
	if (!res)
		res = find_env_value(vars_list, key_word, key_len);
	return (safe_free(key_word), res);
}

char	*find_env_value(t_list *list, char *key_word, int key_len)
{
	char	*res;

	while (list)
	{
		if (!ft_strncmp(list->content, key_word, key_len)
			&& ((char *)list->content)[key_len] == '=')
		{
			res = ft_strdup(&((char *)list->content)[key_len + 1]);
			if (res && ft_strcmp("", res) == 0)
				res = safe_free(res);
			return (res);
		}
		list = list->next;
	}
	return (NULL);
}
