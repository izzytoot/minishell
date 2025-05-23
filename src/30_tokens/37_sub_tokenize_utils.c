/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37_sub_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:37:44 by isabel            #+#    #+#             */
/*   Updated: 2025/05/23 18:38:11 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	attribute_type(t_msh **msh, t_tk_lst *curr)
{
	char 	*word;
	char	*env_path;
	
	env_path = get_path((*msh)->envp_list);
	if (curr->type == WORD || curr->type == ARG)
	{			
		word = ft_strdup(curr->content);
		if (check_builtin(word))
			curr->type = BT_CMD;
		else if (((ft_strcmp(word, ".") != 0) && (ft_strcmp(word, "..") != 0))
			&& (check_env_cmd(word, env_path, -1) || ch_shlvl(msh, word)))
			curr->type = ENV_CMD;
		else
			curr->type = ARG;
		free(word);
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
