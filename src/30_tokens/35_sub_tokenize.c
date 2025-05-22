/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35_sub_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:15 by isabel            #+#    #+#             */
/*   Updated: 2025/05/22 01:11:27 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sub_tokenize(t_msh **msh)
{
	t_tk_lst	*curr;
	char		*word;
	char		*env_path;

	handle_filename(msh);
	join_rest(msh);
	curr = (*msh)->token_list;
	word = NULL;
	env_path = get_path((*msh)->envp_list);
	while (curr)
	{
		if (curr->type == WORD || curr->type == ARG)
		{
			word = curr->content;
			if (check_builtin(word))
				curr->type = BT_CMD;
			else if (check_env_cmd(word, env_path, -1) || (ch_shlvl(word)))
				curr->type = ENV_CMD;
			else
				curr->type = ARG;
			//rm_empties(&curr);
		}
		curr = curr->next;
	}
	check_rep_cmd(&(*msh));
	rm_empties(&(*msh)->token_list);
}

void	handle_filename(t_msh **msh)
{
	t_tk_lst	*curr;
	bool		hd_flag;

	curr = (*msh)->token_list;
	hd_flag = false;
	while (curr)
	{
		if (curr->type == REDIR_HD || curr->type == REDIR_APP
			|| curr->type == REDIR_IN || curr->type == REDIR_OUT)
		{
			if (!curr->prev)
				return;
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
	else if (!(tk_in_qts(tmp_fn->prev)))
		expand_fn(msh, &tmp_fn, NULL, hd_flag);
	if (!tmp_fn->quotes.sp_case && tmp_fn->prev && tmp_fn->prev->type == WORD)
	{
		merge_tg = tmp_fn->prev;
		expand_and_join_fname(msh, tmp_fn, merge_tg, hd_flag);
	}
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
			merge_target = tmp_w->prev;
		else
		{
			if (!merge_target->prev)
			{
				(*msh)->token_list = tmp_w;
				tmp_w->prev = NULL;
			}
			break ;
		}
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
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		safe_free(part_path); //this was causing segfault
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_arrays((void **)paths); //this was causing segfault
			return (cmd_path);
		}
		safe_free(cmd_path); //this was causing segfault
	}
//	ft_free_arrays((void **)paths);
	return (NULL);
}
