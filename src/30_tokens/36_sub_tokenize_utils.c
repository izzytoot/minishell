/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36_sub_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:37:44 by isabel            #+#    #+#             */
/*   Updated: 2025/05/22 15:10:36 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	join_parts(t_tk_lst	**src, t_tk_lst **tg)
{
	char		*cont;

	cont = safe_strjoin((*src)->content, (*tg)->content);
	free((*src)->content);
	(*src)->content = ft_strdup(cont);
	(*src)->quotes.sp_case = (*tg)->quotes.sp_case;
	if ((*tg)->prev)
	{
		(*src)->prev = (*tg)->prev;
		(*src)->prev->next = (*src);
	}
}

bool	ch_shlvl(t_msh **msh, char *word)
{
	t_list	*curr;

	if (ft_strchr(word, '/'))
		return (true);
	if (ft_strcmp(word, "minishell") == 0)
	{
		curr = (*msh)->envp_list;
		while(curr)
		{
			if (ft_strncmp((*msh)->envp_list->content, "PATH=", 5) == 0)
				return (false);
			curr = curr->next;
		}
		return (true);
	}
	return (false);
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
