/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36_sub_tokenize_files.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:33:42 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/29 18:45:52 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_filename(t_msh **msh)
{
	t_tk_lst	*curr;
	bool		hd_flag;

	curr = (*msh)->token_list; //add if !curr
	hd_flag = false;
	while (curr)
	{
		if (curr->type == REDIR_HD || curr->type == REDIR_APP
			|| curr->type == REDIR_IN || curr->type == REDIR_OUT)
		{
			if (!curr->prev)
				return ;
			if (curr->type == REDIR_HD)
				hd_flag = true;
			if (curr->prev->type == W_SPACE && curr->prev->prev->type == WORD)
				curr->prev->prev->type = FILE_NAME;
			else if (curr->prev->type == WORD)
				curr->prev->type = FILE_NAME;
		}
		curr = curr->next;
	}
	join_filename(msh, hd_flag);
}

void	join_filename(t_msh **msh, bool hd_flag)
{
	t_tk_lst	*tmp_fn;
	t_tk_lst	*merge_tg;

	tmp_fn = find_file(msh);
	if (!tmp_fn)
		return ;
	else if (!tmp_fn->prev || (tmp_fn->prev && tmp_fn->prev->type != W_SPACE
			&& !(tk_in_qts(tmp_fn->prev))))
		expand_fn(msh, &tmp_fn, NULL, hd_flag);
	if (!tmp_fn->quotes.sp_case && tmp_fn->prev && tmp_fn->prev->type == WORD)
	{
		merge_tg = tmp_fn->prev;
		expand_and_join_fname(msh, tmp_fn, merge_tg, hd_flag);
	}
}

t_tk_lst	*find_file(t_msh **msh)
{
	t_tk_lst	*file;

	file = (*msh)->token_list;
	while (file)
	{
		if (file->type == FILE_NAME)
			return (file);
		file = file->next;
	}
	return (NULL);
}

void	expand_fn(t_msh **msh, t_tk_lst **tmp_fn, t_tk_lst **merge_tg,
				bool hd_flag)
{
	if (hd_flag)
		return ;
	if (tmp_fn && ft_strchr((*tmp_fn)->content, '$')
		&& !(*tmp_fn)->quotes.in_squotes)
		expand_fname(msh, &(*tmp_fn)->content);
	if (merge_tg && ft_strchr((*merge_tg)->content, '$')
		&& !(*merge_tg)->quotes.in_squotes)
		expand_fname(msh, &(*merge_tg)->content);
	if (merge_tg && (*merge_tg)->quotes.in_squotes)
		(*tmp_fn)->quotes.in_squotes = true;
}
