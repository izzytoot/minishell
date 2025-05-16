/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   74_expand_key_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:48:17 by isabel            #+#    #+#             */
/*   Updated: 2025/05/16 14:25:09 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_kw(t_msh **msh, t_kw **kw_lst)
{
	t_kw	*curr_kw;

	curr_kw = *kw_lst;
	while(curr_kw)
	{
		if (expand_case(curr_kw->kw) == 1 || expand_case(curr_kw->kw) == 4
			|| (expand_case(curr_kw->kw) == 5 && !(*kw_lst)->next))
			;
		else if (expand_case(curr_kw->kw) == 6)
			curr_kw->kw = ft_strdup(ft_itoa((*msh)->msh_pid));
		else if (expand_case(curr_kw->kw) == 2)
			curr_kw->kw = ft_strdup("minishell");
		else if (expand_case(curr_kw->kw) == 3)
			curr_kw->kw = ft_strdup(ft_itoa(exit_value(msh, 0, 0, 0)));
		else if (expand_case(curr_kw->kw) == 7)
		{
			if (curr_kw->exp)
				curr_kw->kw = get_env_cont((*msh)->envp_list, (*msh)->vars_list, curr_kw->kw);
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
	else if(ft_strcmp(kw, "?") == 0)
			return (3);
	else if(ft_strchr(SYM_EXP, kw[0]) || ft_strchr(WS, kw[0]))
		return (4);
	else if (ft_strcmp(kw, "$") == 0)
		return (5);
	else if (ft_strcmp(kw, "$$") == 0)
		return (6);
	return (7);
}

char *get_env_cont(t_list *envp_list, t_list *vars_list, char *key_word)
{
	int		key_len;

	key_len = ft_strlen(key_word);
	while (envp_list)
	{
		if (!ft_strncmp(envp_list->content, key_word, key_len)
				&& ((char *)envp_list->content)[key_len] == '=')
			return(&((char *)envp_list->content)[key_len + 1]);
		envp_list = envp_list->next;
	}
	while (vars_list)
	{
		if (!ft_strncmp(vars_list->content, key_word, key_len)
			&& ((char *)vars_list->content)[key_len] == '=')
			return(&((char *)vars_list->content)[key_len + 1]);
		vars_list = vars_list->next;
	}
	return (NULL);
}

