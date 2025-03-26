/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/26 14:23:10 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd(t_minishell **msh)
{
	char	**args;
	char 	*path;
	
	args = ft_split((*msh)->promt_line, ' ');
	if (args[2])
		return(ft_putstr_fd(ERR_CD_MANY_ARGS, STDERR_FILENO), EXIT_FAILURE);
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = 
	}
	
}
int change_dir(t_minishell **msh, char *path)
{
	char *temp;
	char cwd[PATH_MAX];

	if (chdir(path) != 0)
		return(ft_putstr_fd("No such file or directory", STDERR_FILENO), 1); //fix error
	temp = getcwd(cwd, PATH_MAX);
		return(0);
}

cd_error_handle()
{
	errno = ENOENT;
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return(ft_putstr_fd("\n", STDERR_FILENO), 1);
}