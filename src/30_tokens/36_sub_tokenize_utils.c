/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36_sub_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:37:44 by isabel            #+#    #+#             */
/*   Updated: 2025/05/06 14:38:24 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_filename(t_tk_lst *token_list)
{
	t_tk_lst *curr;

	curr = token_list;
	while (curr)
	{
		if (curr->type == REDIR_HD || curr->type == REDIR_APP 
			|| curr->type == REDIR_IN || curr->type == REDIR_OUT)
		{
			if (curr->prev->type == W_SPACE && curr->prev->prev->type == WORD)
				curr->prev->prev->type = FILE_NAME;
			else if (curr->prev->type == WORD)
				curr->prev->type = FILE_NAME;
		}
		curr = curr->next;
	}
}

char	*check_env_cmd(char *cmd, char *env_path, int i)
{
	char	**paths;
	char	*part_path;
	char	*cmd_path;
	
	paths = ft_split(env_path, ':');
	ft_init_var((void **)&part_path, (void **)&cmd_path, NULL, NULL);
	if (!paths)
		return (0);
	while(paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_arrays((void **)paths);
			return(cmd_path);
		}
		free(cmd_path);
	}
	ft_free_arrays((void **)paths);
	return(NULL);	
}

void	join_filename(t_msh **msh)
{
	t_tk_lst	*tmp_fn;
	t_tk_lst	*merge_target;
	
	tmp_fn = find_file(msh);
	if (!tmp_fn)
		return ;
	if (!tmp_fn->quotes.space_case && tmp_fn->prev)
	{
		merge_target = tmp_fn->prev;
		while (tmp_fn && (!tmp_fn->quotes.space_case && tmp_fn->prev))
		{
			join_parts(&tmp_fn, &merge_target);
			if (!tmp_fn->quotes.space_case && merge_target->prev)
				merge_target = tmp_fn->prev;
			else
			{
				if (!merge_target->prev)
					(*msh)->token_list = tmp_fn;
				break ;
			}
		}
	}
}

void	join_parts(t_tk_lst	**tmp_fn, t_tk_lst **merge_target)
{
	char		*cont;

	cont = ft_strjoin((*tmp_fn)->content, (*merge_target)->content);
	free((*tmp_fn)->content);
	(*tmp_fn)->content = cont;
	(*tmp_fn)->quotes.space_case = (*merge_target)->quotes.space_case;
	if ((*merge_target)->prev)
	{
		(*tmp_fn)->prev = (*merge_target)->prev;
		(*tmp_fn)->prev->next = (*tmp_fn);
	}
}

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

