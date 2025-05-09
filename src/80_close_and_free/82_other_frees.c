/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   82_other_frees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:52:51 by isabel            #+#    #+#             */
/*   Updated: 2025/05/09 16:41:33 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**free_kw_error(char **kw)
{
	ft_dprintf(STDERR_FILENO, ERR_KW);
	ft_free_arrays((void **)kw);
	return (NULL);
}

void	ft_free_str_arr(char **array) //not sure I need this or can just use free_arrays
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if(array[i])
			array[i] = safe_free(array[i]);
		i++;
	}
	if (array)
		array = safe_free(array);
	return ;
}

void	free_tokens(t_tk_lst *token_list)
{
	t_tk_lst	*tmp;

	tmp = token_list;
	while (token_list)
	{
		tmp = token_list->next;
		token_list = safe_free(token_list);
		token_list = tmp;
	}
}

void	free_qt_lst(t_quote *qt_list)
{
	t_quote	*tmp;

	tmp = qt_list;
	while (qt_list)
	{
		tmp = qt_list->next;
		qt_list = safe_free(qt_list);
		qt_list = tmp;
	}
}

/*
void	free_tokens(t_tk_lst *token_list)
{
	t_tk_lst	*tmp;

	tmp = token_list;
	while (token_list)
	{
		tmp = token_list->next;
		if (token_list->content)
			token_list->content = safe_free(token_list->content);
		token_list = tmp;
	}
		token_list = safe_free(token_list);
}
	

void	free_qt_lst(t_quote *qt_list)
{
	t_quote	*tmp;

	tmp = qt_list;
	while (qt_list)
	{
		tmp = qt_list->next;
		if (qt_list->content)
			qt_list->content = safe_free(qt_list->content);
		qt_list = tmp;
	}
	qt_list = safe_free(qt_list);
}
*/