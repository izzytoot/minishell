/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   82_other_frees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:52:51 by isabel            #+#    #+#             */
/*   Updated: 2025/05/14 16:29:35 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	kw_err(void)
{
	ft_dprintf(STDERR_FILENO, ERR_KW);
}

void	ft_free_str_arr(char **array) //not sure I need this or can just use free_arrays
{
	int	i;

	i = 0;
	if (!(*array))
		return ;
	while (array[i])
	{
		if(array[i])
			safe_free(array[i]);
		i++;
	}
	if (array)
		safe_free(array);
	return ;
}

void	free_tokens(t_tk_lst *token_list)
{
	t_tk_lst	*tmp;

	tmp = token_list;
	while (token_list)
	{
		tmp = token_list->next;
		if (token_list->content)
			safe_free(token_list->content);
		token_list = tmp;
	}
	safe_free(token_list);
}

void	free_qt_lst(t_quote *qt_list)
{
	t_quote	*tmp;

	tmp = qt_list;
	while (qt_list)
	{
		tmp = qt_list->next;
		safe_free(qt_list);
		qt_list = tmp;
	}
	safe_free(qt_list);
}

void	free_kw_structs(t_exp_cont *parts, t_kw **kw_lst)
{
	if (parts->new_c)
		safe_free(parts->new_c);
	if (parts->post_c)
		safe_free(parts->post_c);
	if (parts->pre_c)
		safe_free(parts->pre_c);
	(void)kw_lst;
//	while (*kw_lst)
//	{
//		if((*kw_lst)->kw)
//			(*kw_lst)->kw = safe_free((*kw_lst)->kw);
//		*kw_lst = (*kw_lst)->next;
//	}
//	*kw_lst = safe_free(*kw_lst);
}
