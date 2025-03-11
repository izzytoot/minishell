/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_msh_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/11 18:45:32 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_init_msh(t_minishell *msh, char **envp)
{
	if (!isatty(STDIN_FILENO))
		close_minishell(msh, ERR_STDIN, EXIT_FAILURE);
	ft_bzero(&msh, sizeof(t_minishell));
	dup_envp(&msh->envp, envp);
}

void	dup_envp(t_list **dup_envp, char **envp)
{
	t_list	*next_envp;
	int		i;
	char	*temp_envp;
	
	if (!envp || !envp[0])
		exit(1); //change to exit function when we have one
	i = -1;
	while(envp[++i])
	{
		temp_envp = ft_strdup(envp[i]);
		if (!temp_envp)
			exit(1); //change to exit function when we have one
		next_envp = ft_lstnew(temp_envp);
		free (temp_envp);
		if (!next_envp)
			exit(1); //change to exit function when we have one
		ft_lstadd_back(dup_envp, next_envp);
	}
}