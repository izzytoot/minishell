/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/26 18:05:53 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> checks if cd has args, executes cd

int	ft_cd(t_minishell **msh)
{
	char	**args;
	char 	cwd[PATH_MAX];
	
	args = ft_split((*msh)->promt_line, ' ');
	if (args[2])
		return(ft_putstr_fd(ERR_CD_MANY_ARGS, STDERR_FILENO), EXIT_FAILURE);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ft_putstr_fd("error to fix", STDERR_FILENO), errno);
	return (execute_cd(msh, cwd));
}

//info --> changes dir and updates OLDPWD

int execute_cd(t_minishell **msh, char *path)
{
	char **args;
	
	args = ft_split((*msh)->promt_line, ' ');
	if (chdir(args[1]) == EXIT_SUCCESS)
		update_dir(path, &(*msh)->envp_list);
	return (EXIT_SUCCESS);
}
//info --> updates OLDPWD and PWD
//falta verificar se PWD e OLDPWD sao env var, se nao criar

int update_dir(char *old_dir, t_list **envp)
{
	char	new_dir[PATH_MAX];
	
	if (getcwd(new_dir, PATH_MAX) == NULL)
		return(EXIT_FAILURE);
	update_env_var("PWD", new_dir, *envp);
	update_env_var("OLDPWD", old_dir, *envp);
	return (EXIT_SUCCESS);
}

//info --> updates a env var with a new value

void	update_env_var(char *var_name, char *new_data, t_list *envp)
{
	char	*current_env;
	char	*temp;
	int		i;

	while (envp)
	{
		i = 0;
		current_env = (char *)envp->content;
		while (var_name[i] && current_env[i] && (var_name[i] == current_env[i]))
			i++;
		if (!var_name[i] && (current_env[i] == '='))
		{
			temp = ft_strjoin(var_name, "=");
			if (!temp)
				exit(EXIT_FAILURE);
			envp->content = ft_strjoin(temp, new_data);
			if (!envp->content)
				exit(EXIT_FAILURE);
			free(temp);
		}
	}
}
