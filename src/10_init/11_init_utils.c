/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:16 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/18 17:35:44 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_getpid(t_minishell *msh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		close_minishell(msh, RED ERR_PRC RES, EXIT_FAILURE);
	wait (0);
	return (pid);	
}

void	copy_envp(t_minishell *msh, char **envp)
{
	char	*temp_envp;
	t_list	*new_node;
	int		i;

	i = -1;
	msh->l_envp = NULL;
	if (!envp)
		return ;
	while(envp[++i])
	{ 
		temp_envp = ft_strdup(envp[i]);
		if (!temp_envp)
			handle_envp_failure(msh, temp_envp, NULL);
		new_node = ft_lstnew(temp_envp);
		if (!new_node)
		{
			free(temp_envp);
			handle_envp_failure(msh, NULL, new_node);
		}
		ft_lstadd_back(&msh->l_envp, new_node);
	}
}