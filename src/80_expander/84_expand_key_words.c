/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   84_expand_key_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:48:17 by isabel            #+#    #+#             */
/*   Updated: 2025/06/04 15:10:56 by icunha-t         ###   ########.fr       */
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

char	*get_env_cont(t_list *envp_list, t_list *vars_list, char *key_word)
{
	int		key_len;

	key_len = ft_strlen(key_word);
	while (envp_list)
	{
		if (!ft_strncmp(envp_list->content, key_word, key_len)
			&& ((char *)envp_list->content)[key_len] == '=')
			return (safe_free(key_word),
				ft_strdup(&((char *)envp_list->content)[key_len + 1])); //leaks - added free
		envp_list = envp_list->next;
	}
	while (vars_list)
	{
		if (!ft_strncmp(vars_list->content, key_word, key_len)
			&& ((char *)vars_list->content)[key_len] == '=')
			return (safe_free(key_word),
				ft_strdup(&((char *)vars_list->content)[key_len + 1])); //leaks - added free
		vars_list = vars_list->next;
	}
	return (safe_free(key_word));
}

char	**ft_array_dup_null(t_tree_nd *node, char **array, int n)
{
	int		i;
	int		size;
	char	**new_array;

	if (!array)
		return (NULL);
	size = 0;
	i = 0;
	while (n-- > 0)
	{
		if (array[i])
			size++;
		i++;
	}
	node->nb_arg = size;
	new_array = copy_array(size, array);
	return (new_array);
}
