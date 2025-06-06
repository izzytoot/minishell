/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   102_other_frees.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:52:51 by isabel            #+#    #+#             */
/*   Updated: 2025/06/06 17:51:07 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tokens(t_tk_lst *token_list, int n)
{
	t_tk_lst	*tmp;

	tmp = token_list;
	if (n == 1)
	{
		if (token_list->content)
			token_list->content = safe_free(token_list->content);
		if (token_list->quotes.content)
			token_list->quotes.content = safe_free(token_list->quotes.content);
		token_list = safe_free(token_list);
	}
	if (n == 2)
	{
		while (token_list)
		{
			tmp = token_list->next;
			if (token_list->content)
				token_list->content = safe_free(token_list->content);
			if (token_list->quotes.content)
				token_list->quotes.content
					= safe_free(token_list->quotes.content);
			token_list = safe_free(token_list);
			token_list = tmp;
		}
	}
}

void	free_qt_lst(t_quote *qt_list)
{
	t_quote	*tmp;

	while (qt_list)
	{
		tmp = qt_list->next;
		if (qt_list->content)
			qt_list->content = safe_free(qt_list->content);
		qt_list = safe_free(qt_list);
		qt_list = tmp;
	}
	qt_list = safe_free(qt_list);
}

void	free_kw_structs(t_exp_cont *parts, t_kw **kw_lst)
{
	t_kw	*tmp_kw;

	if (parts->new_c)
		parts->new_c = safe_free(parts->new_c);
	if (parts->post_c)
		parts->post_c = safe_free(parts->post_c);
	if (parts->pre_c)
		parts->pre_c = safe_free(parts->pre_c);
	while (*kw_lst)
	{
		tmp_kw = (*kw_lst)->next;
		if ((*kw_lst)->kw)
			safe_free((*kw_lst)->kw);
		safe_free(*kw_lst);
		*kw_lst = tmp_kw;
	}
}
