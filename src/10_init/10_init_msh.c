/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_init_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/12 16:42:36 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_msh(t_msh **msh, char **envp)
{
	(*msh)->hd_check = false;
	(*msh)->empties = false;
	(*msh)->signal = false;
	(*msh)->child = false;
	init_all_null(&(*msh));
	copy_envp(*msh, envp);
	update_shlvl(&(*msh)->envp_list);
	env_i(&(*msh)->envp_list);
	exit_value(msh, 0, 1, 0);
	prompt_and_read(&(*msh));
}

void	prompt_and_read(t_msh **msh)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		start_sigs();
		prompt = get_prompt(*msh);
		line = readline(prompt);
		free(prompt);
		if (!line)
			close_msh_prompt(msh);
		if (*line)
			add_history (line);
		(*msh)->token_list = NULL;
		(*msh)->prompt_line = line;
		if (line && (syntax_is_ok(&(*msh)) == 0))
		{
			get_tokens(&(*msh), -1);
			exec_tree(&(*msh), (*msh)->tree_root);
		}
		if ((*msh)->debug_mode)
			ft_printf("status is %d\n", exit_value(msh, 0, 0, 0));
		free_prompt_line(&(*msh));
	}
}

char	*get_display_path(t_msh *msh)
{
	char	*cwd;
	char	*backup;

	cwd = safe_getcwd(msh, true);
	if (cwd && access(cwd, F_OK) == 0)
		return (cwd);
	if (cwd)
		free(cwd);
	backup = get_var_val(msh->envp_list, "PWD");
	if (backup)
		return (ft_strtrim(backup, "\n"));
	return (ft_strdup("[unknown]"));
}

char	*get_prompt(t_msh *msh)
{
	char	*path;
	char	*prompt;
	char	*colored_prefix;
	char	*tmp;

	path = get_display_path(msh);
	if (!path)
		return (ft_strdup("$ "));
	colored_prefix = ft_strjoin(BBLU "Minishell: ", RES);
	if (!colored_prefix)
		return (free(path), ft_strdup("$ "));
	tmp = ft_strjoin(colored_prefix, path);
	free(colored_prefix);
	free(path);
	if (!tmp)
		return (ft_strdup("$ "));
	prompt = ft_strjoin(tmp, " $ ");
	free(tmp);
	if (!prompt)
	{
		perror("ft_strjoin");
		return (ft_strdup("$ "));
	}
	return (prompt);
}

int	exit_value(t_msh **msh, int exit_code, int upd_exit, int close)
{
	static int	current_code;

	if (!msh)
		(void)msh;
	if (upd_exit == 1)
		current_code = exit_code;
	if (close == 1)
		close_minishell(*msh, current_code);
	return (current_code);
}
