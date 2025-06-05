/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37_sub_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:37:44 by isabel            #+#    #+#             */
/*   Updated: 2025/06/05 12:16:18 by icunha-t         ###   ########.fr       */
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

bool	look_for_exp(t_tk_lst *curr, char *word)
{
	int	i;

	i = -1;
	if (curr->quotes.in_squotes)
		return (false);
	while (word[++i])
	{
		if (word[i] == '$')
			return (true);
	}
	return (false);
}

char	*check_env_cmd(char *cmd, char *env_path, int i, int n)
{
	char	**paths;
	char	*part_path;
	char	*cmd_path;

	paths = ft_split(env_path, ':');
	ft_init_var((void **)&part_path, (void **)&cmd_path, NULL, NULL);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		get_cmd_path(paths[i], &part_path, &cmd_path, cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_arrays((void **)paths);
			if (n == 1) //leaks - added case 1 for freeing cmd_path when not used
			{
				cmd_path = safe_free(cmd_path);
				return ("true");
			}
			return (cmd_path);
		}
		cmd_path = safe_free(cmd_path);
	}
	ft_free_arrays((void **)paths);
	return (NULL);
}

void	get_cmd_path(char	*path, char	**part_path, char **cmd_path, char *cmd) //leaks - added function to reduce lines
{
	*part_path = ft_strjoin(path, "/");
	*cmd_path = ft_strjoin(*part_path, cmd);
	*part_path = safe_free(*part_path);
}

void	join_parts(t_tk_lst **src, t_tk_lst **tg)
{
	char		*cont;

	cont = safe_strjoin((*src)->content, (*tg)->content);
	(*src)->content = cont;
	if ((*src)->quotes.content)
		(*src)->quotes.content = safe_free((*src)->quotes.content); //leaks added line
	(*src)->quotes.content = ft_strdup(cont);
	(*src)->quotes.sp_case = (*tg)->quotes.sp_case;
	if ((*tg)->prev)
	{
		(*src)->prev = (*tg)->prev;
		(*src)->prev->next = (*src);
	}
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
