/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_msh_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/12 17:06:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_init_msh(t_minishell *msh, int ac, char **av, char **envp)
{
	(void)ac;
	if (!isatty(STDIN_FILENO))
		close_minishell(msh, RED ERR_STDIN RES, EXIT_FAILURE);
	msh->msh_pid = my_getpid(msh);
	if (av[0][0] == '.' && av[0][1] == '/')
		msh->prog_name = ft_strdup(av[0] + 2);
	else
		msh->prog_name = NULL; //no program, right?
	dup_envp(msh, &msh->l_envp, envp);
	/*
	ft_printf("minishel:\npid: $d\nprog name: %s\n", msh->msh_pid, msh->prog_name);
	while(msh->l_envp)
	{
		ft_printf("%s\n", msh->l_envp->content);
		msh->l_envp = msh->l_envp->next;
	}
	*/
	close_minishell(msh, NULL, EXIT_SUCCESS);
}

int	my_getpid(t_minishell *msh)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		close_minishell(msh, RED ERR_PRC RES, EXIT_FAILURE);
	wait (0);
	return (pid);	
}

void	dup_envp(t_minishell *msh, t_list **l_envp, char **envp)
{
	t_list	*next_envp;
	char	*temp_envp;
	int		i;

	i = -1;
	if (!envp || !envp[0])
	{
		*l_envp = NULL; // no envp is possible?
		return ;
	}
	while(envp[++i])
	{ 
		temp_envp = ft_strdup(envp[i]);
		if (!temp_envp)
			handle_envp_failure(msh, temp_envp, NULL);
		next_envp = ft_lstnew(temp_envp);
		if (!next_envp)
			handle_envp_failure(msh, NULL, next_envp);
		ft_lstadd_back(l_envp, next_envp);
	}
}