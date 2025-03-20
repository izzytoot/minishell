/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_init_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/20 12:35:49 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_init_msh(t_minishell **msh, char **envp)
{
	if (!isatty(STDIN_FILENO))
		close_minishell(*msh, RED ERR_STDIN RES, EXIT_FAILURE);
	init_all_null(&(*msh));
	//(*msh)->msh_pid = my_getpid(*msh); // needs 2 exit when activated
	copy_envp(*msh, envp);
	if ((*msh)->debug_mode)
		print_envp_in_struct(&(*msh)); //DEBUG TO DELETE
	prompt_and_read(&(*msh));
}


void	prompt_and_read(t_minishell **msh)
{
	char *line;
	
	(*msh)->dir = getcwd(NULL, 1024); //perceber 1024
	while (1)
	{
		line = readline("$ ");
		add_history(line);
		(*msh)->token_list = NULL;
		(*msh)->promt_line = line;
		if (strncmp(line, "pwd", 3) == 0) // ???
			printf("%s\n", (*msh)->dir);
		if (strncmp(line, "exit", 4) == 0) // ??
		{
			ft_printf("exit\n");
			free(line);
			close_minishell(*msh, NULL, EXIT_SUCCESS);
		}
		if (syntax_is_ok(&(*msh)))
			get_tokens(&(*msh));
		if ((*msh)->debug_mode)
			print_tokens(&(*msh)); //DEBUG TO DELETE
		free(line);
	}
}