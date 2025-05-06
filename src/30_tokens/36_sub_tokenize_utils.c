/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36_sub_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:37:44 by isabel            #+#    #+#             */
/*   Updated: 2025/05/06 16:22:12 by isabel           ###   ########.fr       */
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

void	join_parts(t_tk_lst	**src, t_tk_lst **target)
{
	char		*cont;

	cont = ft_strjoin((*src)->content, (*target)->content);
	free((*src)->content);
	(*src)->content = cont;
	(*src)->quotes.space_case = (*target)->quotes.space_case;
	if ((*target)->prev)
	{
		(*src)->prev = (*target)->prev;
		(*src)->prev->next = (*src);
	}
}
