/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/03 18:43:54 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> executes cd, updates env var

int	ft_cd(t_minishell **msh)
{
	char	*target_dir;
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	**args;

	args = ft_split((*msh)->promt_line, ' ');
	if (!args || !args[0])
		return (ft_free_arrays((void **)args), EXIT_FAILURE);
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("cd: getcwd");
		return (ft_free_arrays((void **)args), EXIT_FAILURE);
	}
	old_pwd = ft_strjoin(ft_strdup(cwd), "\n");
	if (get_dir(args, &target_dir) != EXIT_SUCCESS)
		return (free(old_pwd), ft_free_arrays((void **)args), EXIT_FAILURE);
	if (chdir(target_dir) == -1)
	{
		perror("cd");
		return (free(old_pwd), ft_free_arrays((void **)args), EXIT_FAILURE);
	}
	update_cd_env(msh, old_pwd);
	return (free(old_pwd), ft_free_arrays((void **)args), EXIT_SUCCESS);
}

//info --> get target dir

int	get_dir(char **args, char **target_dir)
{
	if (!args[1])
	{
		*target_dir = getenv("HOME");
		if (!*target_dir)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else
		*target_dir = args[1];
	return (EXIT_SUCCESS);
}

//info --> updates OLDPWD and PWD
//falta verificar se PWD e OLDPWD sao env var, se nao criar

int	update_cd_env(t_minishell **msh, char *old_pwd)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (update_env_var(&(*msh)->envp_list, "OLDPWD", old_pwd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: getcwd");
		return (EXIT_FAILURE);
	}
	pwd = ft_strjoin(cwd, "\n");
	if (update_env_var(&(*msh)->envp_list, "PWD", pwd) != EXIT_SUCCESS)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	free(pwd);
	return (EXIT_SUCCESS);
}
