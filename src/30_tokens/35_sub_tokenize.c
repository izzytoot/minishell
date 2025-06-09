/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35_sub_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:15 by isabel            #+#    #+#             */
/*   Updated: 2025/06/08 23:17:13 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sub_tokenize(t_msh **msh)
{
	t_tk_lst	*curr;

	handle_filename(msh);
	join_rest(msh);
	curr = (*msh)->token_list;
	while (curr)
	{
		attribute_type(msh, curr);
		curr = curr->next;
	}
	check_rep_cmd(&(*msh));
	if ((*msh)->empties && (*msh)->token_list && (*msh)->token_list->content)
		rm_empties(&(*msh)->token_list);
}

void	join_rest(t_msh **msh)
{
	t_tk_lst	*tmp_w;
	t_tk_lst	*merge_target;

	if ((*msh)->token_list && !(*msh)->token_list->next)
		return ;
	tmp_w = find_w_tk(msh);
	if (!tmp_w)
		return ;
	merge_target = tmp_w->prev;
	while (tmp_w && (!tmp_w->quotes.sp_case && tmp_w->prev)
		&& tmp_w->prev->content[0] != '$')
	{
		join_parts(&tmp_w, &merge_target);
		join_rest_util(msh, merge_target, tmp_w);
		if (find_w_tk(msh))
			join_rest(msh);
		else
			break ;
	}
}

void	join_rest_util(t_msh **msh, t_tk_lst *mg_tg, t_tk_lst *tmp_w)
{
	if (!tmp_w->quotes.sp_case && mg_tg->prev)
		rm_joined_tk(msh, &mg_tg, &tmp_w, 1);
	else
	{
		if (!mg_tg->prev)
			rm_joined_tk(msh, &mg_tg, &tmp_w, 2);
		else
			free_tokens(mg_tg, 1);
	}
}

void	rm_joined_tk(t_msh **msh, t_tk_lst **mg_tg, t_tk_lst **tmp_w, int n)
{
	if (n == 1)
	{
		free_tokens(*mg_tg, 1);
		*mg_tg = (*tmp_w)->prev;
	}
	if (n == 2)
	{
		free_tokens(*mg_tg, 1);
		(*msh)->token_list = *tmp_w;
		(*tmp_w)->prev = NULL;
	}
}

void	attribute_type(t_msh **msh, t_tk_lst *curr)
{
	char	*word;
	char	*env_path;

	env_path = get_path((*msh)->envp_list);
	if (curr->type == WORD || curr->type == ARG)
	{
		word = ft_strdup(curr->content);
		if (check_builtin(word))
			curr->type = BT_CMD;
		else if (((ft_strcmp(word, ".") != 0) && (ft_strcmp(word, "..") != 0))
			&& (check_env_cmd(word, env_path, -1, 1) || ch_shlvl(msh, word)))
			curr->type = ENV_CMD;
		else
			curr->type = ARG;
		if (look_for_exp(curr, word))
			curr->quotes.exp = true;
		word = safe_free(word);
	}
}
