/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:37 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/03/29 16:47:43 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//info --> checks if cd has args, executes cd

int	ft_cd(t_minishell **msh)
{
	int		i;
	char 	cwd[PATH_MAX];

	i = 0;
	while ((*msh)->tree_root->args[i])
	{
		if ((*msh)->tree_root->type == WORD && ft_strncmp((*msh)->tree_root->args[0], "cd", 2) == 0)
		{
			if ((*msh)->tree_root->args[2]) 
			{
                ft_putstr_fd(ERR_CD_MANY_ARGS, STDERR_FILENO);
                return (EXIT_FAILURE);
            }
			if (getcwd(cwd, PATH_MAX) == NULL) 
			{
                ft_putstr_fd("error to fix", STDERR_FILENO);
                return (errno);
            }
			return execute_cd(msh, cwd);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//info --> changes dir and updates OLDPWD

int execute_cd(t_minishell **msh, char *path)
{
	char **args;
	
	args = ft_split((*msh)->promt_line, ' ');
	if (chdir(args[1]) == EXIT_SUCCESS)
		update_dir(path, &(*msh)->envp_list);
	else
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
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

int	update_env_var(char *var_name, char *new_data, t_list *envp)
{
	char	*current_env;
	char	*temp;
	char *new_content;

	while (envp)
	{
		current_env = (char *)envp->content;
		if (ft_strncmp(current_env, var_name, ft_strlen(var_name)) == 0 &&
			current_env[ft_strlen(var_name)] == '=') 
		{
			temp = ft_strjoin(var_name, "=");
            if (!temp)
                return EXIT_FAILURE;
			new_content = ft_strjoin(temp, new_data);
			free(temp);
			if (!new_content)
                return EXIT_FAILURE;
				free(envp->content);
            envp->content = new_content;
            return EXIT_SUCCESS;
		}
	}
		envp = envp->next;
		temp = ft_strjoin(var_name, "=");
		if (!temp)
    		return EXIT_FAILURE;
		new_content = ft_strjoin(temp, new_data);
		free(temp);
		if (!new_content)
        	return EXIT_FAILURE;
		t_list *new_node = ft_lstnew(new_content);
		if (!new_node)
			return EXIT_FAILURE;
		ft_lstadd_back(&envp, new_node);
		return EXIT_SUCCESS;
	}
