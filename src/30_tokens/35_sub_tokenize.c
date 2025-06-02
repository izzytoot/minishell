/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35_sub_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:15 by isabel            #+#    #+#             */
/*   Updated: 2025/06/02 13:03:27 by icunha-t         ###   ########.fr       */
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
		if (!tmp_w->quotes.sp_case && merge_target->prev)
			rm_joined_tk(msh, &merge_target, &tmp_w, 1);
		else
		{
			if (!merge_target->prev)
				rm_joined_tk(msh, &merge_target, &tmp_w, 2);
			break ;
		}
	}
}

t_tk_lst	*find_w_tk(t_msh **msh)
{
	t_tk_lst	*w_tk;

	w_tk = (*msh)->token_list;
	while (w_tk)
	{
		w_tk = w_tk->next;
		if (!w_tk->next)
			break ;
	}
	while (w_tk)
	{
		if (w_tk->type == WORD
			&& !ft_strnstr(w_tk->content, "$", ft_strlen(w_tk->content))
			&& w_tk->prev && w_tk->prev->type == WORD
			&& !w_tk->quotes.sp_case)
			return (w_tk);
		w_tk = w_tk->prev;
	}
	return (NULL);
}

void	rm_joined_tk(t_msh **msh, t_tk_lst **mg_tg, t_tk_lst **tmp_w, int n) //leaks - created fuction to remove unused tokens
{
	if (n == 1)
	{
		free_tokens(*mg_tg, 1);
		*mg_tg = (*tmp_w)->prev;
	}
	if (n == 2)
	{
		free_tokens(*mg_tg, 1); // leaks, added line
		(*msh)->token_list = *tmp_w;
		(*tmp_w)->prev = NULL;	
	}
}
