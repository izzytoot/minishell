/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:16 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/09 13:43:54 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_all_null(t_msh **msh)
{
	(*msh)->prompt_line = NULL;
	(*msh)->token_list = NULL;
	(*msh)->envp = NULL;
	(*msh)->envp_list = NULL;
	(*msh)->vars_list = NULL;
	(*msh)->export_only = NULL;
	(*msh)->tree_root = NULL;
	(*msh)->tmp_fname = NULL;
}

bool	ch_shlvl(t_msh **msh, char *word)
{
	t_list	*curr;

	if (!word)
		return (false);
	if (ft_strchr(word, '/'))
		return (true);
	if (ft_strcmp(word, "minishell") == 0)
	{
		curr = (*msh)->envp_list;
		while (curr)
		{
			if (ft_strncmp((*msh)->envp_list->content, "PATH=", 5) == 0)
				return (false);
			curr = curr->next;
		}
		return (true);
	}
	return (false);
}

bool	ch_shlvl_bin(t_msh **msh, char *word)
{
	t_list	*curr;

	if (!word)
		return (false);
	if (ft_strncmp(word, "/bin/", 5) == 0)
		return (false);
	if (ft_strchr(word, '/'))
		return (true);
	if (ft_strcmp(word, "minishell") == 0)
	{
		curr = (*msh)->envp_list;
		while (curr)
		{
			if (ft_strncmp((*msh)->envp_list->content, "PATH=", 5) == 0)
				return (false);
			curr = curr->next;
		}
		return (true);
	}
	return (false);
}

char	*get_errmsg(void)
{
	int		errnum;
	char	*errmsg;

	errnum = errno;
	errmsg = strerror(errnum);
	return (errmsg);
}

void	free_and_clear(char *str, t_list *lst)
{
	if (str)
		str = safe_free(str);
	if (lst)
		ft_lstclear(&lst, free);
}
