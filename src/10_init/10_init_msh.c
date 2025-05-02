/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_init_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/30 18:01:24 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_msh(t_msh **msh, char **envp)
{	
	// if (!isatty(STDIN_FILENO)) // nao funciona com tester
	// 	close_minishell(*msh, EXIT_FAILURE);
	(*msh)->hd_check = true;
	init_all_null(&(*msh));
	copy_envp(*msh, envp);
//	if ((*msh)->debug_mode)
//		print_envp_in_struct(&(*msh)); //DEBUG TO DELETE
	exit_value(msh, 0, 1, 0); //iniciar o exit_code status
	prompt_and_read(&(*msh));
}

void	prompt_and_read(t_msh **msh)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		if ((*msh)->prompt_line)
		{
			free((*msh)->prompt_line); //safe_free was causing double free
			(*msh)->prompt_line = NULL;
		}
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line) //corrigir. isto é para quando abre nove prompt antes do tempo
			break ;
		add_history (line);
		(*msh)->token_list = NULL;
		(*msh)->prompt_line = line;
		if (line && syntax_is_ok(&(*msh)))
		{
			get_tokens(&(*msh), -1);
			exec_tree(&(*msh), (*msh)->tree_root);
		}
		if ((*msh)->debug_mode)
			ft_printf("status is %d\n", exit_value(msh, 0, 0, 0));
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

int	exit_value(t_msh **msh, int exit_code, int upd_exit, int close)
{
static int	current_code;

if (upd_exit == true)
	current_code = exit_code;
if (close == true)
	close_minishell(*msh, current_code);
return (current_code);
}
