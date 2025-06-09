/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   61_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/09 19:34:39 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(t_msh **msh, t_tree_nd **node)
{
	char	*target_dir;
	char	*old_pwd;
	char	*cwd;

	if (!node || !*node)
		return (EXIT_FAILURE);
	if ((*node)->nb_arg > 1)
		return (ft_putstr_fd(ERR_CD_ARGS, STDERR_FILENO), EXIT_FAILURE);
	old_pwd = safe_getcwd(*msh, true);
	if (!old_pwd)
		return (EXIT_FAILURE);
	if (get_dir(msh, node, &target_dir) == EXIT_FAILURE)
		return (free(old_pwd), EXIT_FAILURE);
	if (chdir(target_dir) == -1)
	{
		ft_dprintf(STDERR_FILENO, "msh: cd: %s: %s\n", target_dir,
			get_errmsg());
		return (free(target_dir), free(old_pwd), EXIT_FAILURE);
	}
	cwd = safe_getcwd(*msh, false);
	if (!cwd)
		return (free(target_dir), free(old_pwd),
			ft_putstr_fd(ERR_2FOLDER, STDERR_FILENO), EXIT_FAILURE);
	update_cd_env(msh, old_pwd);
	return (free(target_dir), free(old_pwd), free(cwd), EXIT_SUCCESS);
}

char	*safe_getcwd(t_msh *msh, bool silent)
{
	char		cwd[PATH_MAX];
	char		*backup;
	static bool	error_printed;

	if (getcwd(cwd, sizeof(cwd)))
		return (error_printed = false, ft_strdup(cwd));
	if (!silent && !error_printed)
	{
		ft_putstr_fd(ERR_2FOLDER, STDERR_FILENO);
		ft_putstr_fd(ERR_2FD_2, STDERR_FILENO);
		error_printed = true;
	}
	backup = get_var_val(msh->envp_list, "PWD");
	if (!backup)
	{
		if (!silent && !error_printed)
		{
			perror("cd: getcwd and no backup PWD");
			error_printed = true;
		}
		return (NULL);
	}
	return (ft_strdup(backup));
}

int	get_dir(t_msh **msh, t_tree_nd **node, char **target_dir)
{
	char	*home;

	if (!node || !*node)
		return (EXIT_FAILURE);
	if (!(*node)->args || ((*node)->args[0]
			&& ft_strcmp((*node)->args[0], "~") == 0))
	{
		home = get_var_val((*msh)->envp_list, "HOME");
		if (!home)
		{
			ft_putstr_fd("msh: cd: HOME not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		*target_dir = ft_strdup(home);
	}
	else
		*target_dir = ft_strdup((*node)->args[0]);
	return (EXIT_SUCCESS);
}

int	update_cd_env(t_msh **msh, char *old_pwd)
{
	char	*cwd;
	char	*pwd;

	if (update_cd_var(&(*msh)->envp_list, "OLDPWD", old_pwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	cwd = safe_getcwd(*msh, true);
	if (!cwd)
	{
		perror("cd: getcwd");
		return (EXIT_FAILURE);
	}
	pwd = ft_strjoin(cwd, "\n");
	free(cwd);
	if (!pwd)
		return (EXIT_FAILURE);
	if (update_cd_var(&(*msh)->envp_list, "PWD", pwd) != EXIT_SUCCESS)
		return (free(pwd), EXIT_FAILURE);
	return (free(pwd), EXIT_SUCCESS);
}

int	update_cd_var(t_list **env_list, const char *var_name, const char *data)
{
	t_list	*current;
	size_t	var_name_len;
	char	*new_entry;
	char	*joined_value;

	var_name_len = ft_strlen(var_name);
	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->content, var_name, var_name_len) == 0
			&& ((char *)(current->content))[var_name_len] == '=')
		{
			free(current->content);
			joined_value = ft_strjoin(var_name, "=");
			new_entry = ft_strjoin(joined_value, data);
			free(joined_value);
			if (!new_entry)
				return (EXIT_FAILURE);
			current->content = new_entry;
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
