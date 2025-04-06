/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/07 12:59:41 by icunha-t         ###   ########.fr       */
=======
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/04 11:45:33 by ddo-carm         ###   ########.fr       */
>>>>>>> 509bd70 (added dprintf, and did norm on libft)
=======
/*   Updated: 2025/04/06 21:28:32 by ddo-carm         ###   ########.fr       */
>>>>>>> 493c1e9 (echo and env updated to binary tree)
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> executes cd, updates env var

int	ft_cd(t_minishell **msh, t_tree_node **node)
{
	char	*target_dir;
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (!node || !*node)
		return (EXIT_FAILURE);
	if ((*node)->args[1])
	{
		ft_putstr_fd(ERR_CD_ARGS, STDERR_FILENO);
<<<<<<< HEAD
		ft_printf("arg 1: %s\n", (*node)->args[1]);
		return (EXIT_FAILURE);
=======
		return (ft_free_arrays((void **)args), EXIT_FAILURE);
>>>>>>> 509bd70 (added dprintf, and did norm on libft)
	}
	if (!getcwd(cwd, PATH_MAX))
		return (perror("cd: getcwd"), EXIT_FAILURE);
	old_pwd = ft_strjoin(ft_strdup(cwd), "\n");
	if (get_dir(&(*node), &target_dir) != EXIT_SUCCESS)
		return (free(old_pwd), EXIT_FAILURE);
	if (chdir(target_dir) == -1)
	{
		ft_printf("msh: cd: %s: No such file or directory\n", target_dir);
		return (free(old_pwd), EXIT_FAILURE);
	}
	update_cd_env(msh, old_pwd);
	return (free(old_pwd), EXIT_SUCCESS);
}

//info --> get target dir

int	get_dir(t_tree_node **node, char **target_dir)
{
	if (!node || !*node)
		return (EXIT_FAILURE);
	if (!(*node)->args[0])
	{
		*target_dir = getenv("HOME");
		if (!*target_dir)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else
		*target_dir = (*node)->args[0];
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
	if (!pwd)
		return (EXIT_FAILURE);
	if (update_env_var(&(*msh)->envp_list, "PWD", pwd) != EXIT_SUCCESS)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	free(pwd);
	return (EXIT_SUCCESS);
}
