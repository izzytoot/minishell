/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_msh_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/18 17:30:19 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_init_msh(t_minishell **msh, char **envp)
{
	if (!isatty(STDIN_FILENO))
		close_minishell(*msh, RED ERR_STDIN RES, EXIT_FAILURE);
	(*msh)->msh_pid = my_getpid(*msh);
	copy_envp(*msh, envp);
	prompt_and_read(&(*msh));
}

void	prompt_and_read(t_minishell **msh)
{
	char *line;
	char buffer[1024];
	
	(*msh)->dir = getcwd(NULL, 1024); //perceber 1024
	while ((line = readline("$ ")) != NULL)
	{
		strncpy(buffer, line, 1024);
		add_history(buffer);
		(*msh)->promt_line = buffer;
		if (strncmp(buffer, "pwd", 3) == 0) // ???
			printf("%s\n", (*msh)->dir);
		if (strncmp(buffer, "exit", 4) == 0)
		{
			ft_printf("exit\n");
			free(line);
			close_minishell(*msh, NULL, EXIT_SUCCESS);
		}
		if (syntax_is_ok(&(*msh)))
			get_tokens(&(*msh));
		free(line);
	}
}