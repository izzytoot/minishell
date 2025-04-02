/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_envp_copies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:44:25 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/02 19:19:26 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	copy_envp(t_minishell *msh, char **envp)
{
	if (!envp)
		return ;
	msh->envp = envp_to_array(msh, envp);
	msh->envp_list = NULL;
	envp_to_list(msh, envp);
}

char	**envp_to_array(t_minishell *msh, char **envp)
{
	int		i;
	int		count;
	char	**envp_array;

	i = -1;
	count = 0;
	while(envp[count])
		count++;
	envp_array = malloc(sizeof(char *) * (count + 1));
	if (!envp_array)
		handle_envp_failure(msh, NULL, NULL, NULL);
	while(++i < count)
	{
		envp_array[i] = ft_strdup(envp[i]);
		if (!envp_array)
		{
			while(--i >= 0)
				free(envp_array[i]);
			free(envp_array);
			handle_envp_failure(msh, NULL, NULL, NULL);
		}
	}
	envp_array[count] = NULL;
	return(envp_array);
}

void	envp_to_list(t_minishell *msh, char **envp)
{
	int		i;
	int		len;
	char	*temp_envp;
	t_list	*new_node;
	
	i = -1;
	ft_init_var((void **)&temp_envp, (void **)&new_node, NULL, NULL);
	while(envp[++i])
	{ 
		temp_envp = ft_strdup(envp[i]);
		if (!temp_envp)
			handle_envp_failure(msh, temp_envp, NULL, NULL);
		len = ft_strlen(envp[i]);
		if (envp[i][len - 1] != '\n')
			temp_envp = add_envp_newline(temp_envp);
		new_node = ft_lstnew(temp_envp);
		if (!new_node)
		{
			free(temp_envp);
			handle_envp_failure(msh, NULL, new_node, NULL);
		}
		ft_lstadd_back(&msh->envp_list, new_node);
	}
}
char *add_envp_newline(char *envp)
{
	char *temp;

	temp = ft_strjoin(envp, "\n");
	free(envp);
	envp = temp;
	return(temp);
}
