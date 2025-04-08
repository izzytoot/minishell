/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_init_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/08 19:30:03 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_init_msh(t_minishell **msh, char **envp)
{
	if (!isatty(STDIN_FILENO))
		close_minishell(*msh, EXIT_FAILURE);
	init_all_null(&(*msh));
	copy_envp(*msh, envp);
//	if ((*msh)->debug_mode)
//		print_envp_in_struct(&(*msh)); //DEBUG TO DELETE
	prompt_and_read(&(*msh));
}

void	prompt_and_read(t_minishell **msh)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		if ((*msh)->prompt_line)
		{	
			free((*msh)->prompt_line);
			(*msh)->prompt_line = NULL;
		}
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		add_history(line);
		(*msh)->token_list = NULL;
		(*msh)->prompt_line = line;
		if (strncmp(line, "exit", 4) == 0)
		{
			if (syntax_is_ok(&(*msh)))
				get_tokens(&(*msh), -1, '\0');
			ft_printf("exit\n");
			free_prompt_line(&(*msh));
			close_minishell(*msh, EXIT_SUCCESS);
		}
		if (syntax_is_ok(&(*msh)))
		{
			get_tokens(&(*msh), -1, '\0');
			// if (!(*msh)->tree_root->left && !(*msh)->tree_root->right)
			// 	exec_single_cmd(&(*msh), NULL);
			// else
			exec_tree(&(*msh), (*msh)->tree_root);
		}
		free_prompt_line(&(*msh));
	}
}

//info --> create prompt wih current dir

char	*get_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (ft_strdup("$ "));
	}
	prompt = ft_strjoin(cwd, " $ ");
	if (!prompt)
	{
		perror("ft_strjoin");
		return (ft_strdup("$ "));
	}
	return (prompt);
}
