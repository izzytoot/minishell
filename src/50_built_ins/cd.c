/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/30 17:32:15 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> checks if cd has args, executes cd

int	ft_cd(t_minishell **msh)
{
	char 	*target_dir;
	char	**args;
	
	args = ft_split((*msh)->promt_line, ' ');
	if (!args || !args[0])
    {
        ft_free_arrays((void **)args);
        return (EXIT_FAILURE);
    }
	target_dir = NULL;
	if (!args[1])
		cd_home(args, target_dir);
	else
		target_dir = args[1];
	change_dir(args, target_dir);
	// ft_free_arrays((void **)args);
	return (EXIT_SUCCESS);
}

int  cd_home(char **args, char *target_dir)
{
	if (!args[1])
    {
        target_dir = getenv("HOME");
        if (!target_dir)
        {
            ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
            ft_free_arrays((void **)args);
            return (EXIT_FAILURE);
        }
	}
	return(EXIT_SUCCESS);
}

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


