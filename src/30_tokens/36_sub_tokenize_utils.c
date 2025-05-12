/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36_sub_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:37:44 by isabel            #+#    #+#             */
/*   Updated: 2025/05/12 20:16:30 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tk_lst	*find_file(t_msh **msh)
{
	t_tk_lst *file;
	
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
	t_tk_lst *w_tk;
	
	w_tk = (*msh)->token_list;
	while (w_tk)
	{
		w_tk = w_tk->next;
		if (!w_tk->next)
			break ;	
	}
	while (w_tk)
	{
		if (w_tk->type == WORD && !ft_strnstr(w_tk->content, "$", ft_strlen(w_tk->content))
			&& w_tk->prev && w_tk->prev->type == WORD 
			&& !w_tk->quotes.space_case)
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
	(*src)->content = cont;
	(*src)->quotes.space_case = (*tg)->quotes.space_case;
	if ((*tg)->prev)
	{
		(*src)->prev = (*tg)->prev;
		(*src)->prev->next = (*src);
	}
}

bool	ch_shlvl(char *word)
{
	if ((word[0] == '.' && word[1] == '/') || ft_strcmp("/bin/ls", word) == 0)
		return (true);
	return (false);
}

void	expand_fn(t_msh **msh, t_tk_lst **tmp_fn, t_tk_lst **merge_tg, bool hd_flag)
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

/*
void	expand_fn(t_msh **msh, t_tk_lst **tmp_fn, t_tk_lst **merge_tg)
{
	if ((*tmp_fn)->content[0] == '$' && !(*tmp_fn)->quotes.in_squotes)
		(*tmp_fn)->content = ft_strdup(get_env_cont((*msh)->envp_list,
			(*msh)->vars_list, (*tmp_fn)->content + 1));		
	if ((*merge_tg)->content[0] == '$' && !(*merge_tg)->quotes.in_squotes)
		(*merge_tg)->content = ft_strdup(get_env_cont((*msh)->envp_list,
			(*msh)->vars_list, (*merge_tg)->content + 1));
}
*/