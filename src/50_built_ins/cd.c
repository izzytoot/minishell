/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/02 14:22:06 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> checks if cd has args, executes cd

int	ft_cd(t_minishell **msh)
{
	char	*target_dir;
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	**args;

	args = ft_split((*msh)->promt_line, ' ');
	if (!args || !args[0])
	{
		ft_free_arrays((void **)args);
		return (EXIT_FAILURE);
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("cd: getcwd");
		ft_free_arrays((void **)args);
		return (EXIT_FAILURE);
	}
	old_pwd = ft_strdup(cwd);
	old_pwd = ft_strjoin(old_pwd, "\n");
	if (!args[1])
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			free(old_pwd);
			ft_free_arrays((void **)args);
			return (EXIT_FAILURE);
		}
	}
	else
		target_dir = args[1];
	if (chdir(target_dir) == -1)
	{
		perror("cd");
		free(old_pwd);
		ft_free_arrays((void **)args);
		return (EXIT_FAILURE);
	}
	update_cd_env(msh, old_pwd);
	free(old_pwd);
	ft_free_arrays((void **)args);
	return (EXIT_SUCCESS);
}

// int  cd_home(char **args, char *target_dir)
// {
// 	if (!args[1])
//     {
//         target_dir = getenv("HOME");
//         if (!target_dir)
//         {
//             ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
//             ft_free_arrays((void **)args);
//             return (EXIT_FAILURE);
//         }
// 	}
// 	return(EXIT_SUCCESS);
// }

int	change_dir(char **args, char *target_dir)
{
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(target_dir, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_free_arrays((void **)args);
		return (EXIT_FAILURE);
	}
	ft_free_arrays((void **)args);
	return (EXIT_SUCCESS);
}

//info --> updates OLDPWD and PWD
//falta verificar se PWD e OLDPWD sao env var, se nao criar

int	update_cd_env(t_minishell **msh, char *old_pwd)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_env_var(&(*msh)->envp_list, "OLDPWD", old_pwd);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd");
		return (EXIT_FAILURE);
	}
	pwd = ft_strjoin(cwd, "\n");
	update_env_var(&(*msh)->envp_list, "PWD", pwd);
	return (EXIT_SUCCESS);
}
