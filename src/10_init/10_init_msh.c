/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_init_msh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:54 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/06 18:46:08 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_init_msh(t_minishell **msh, char **envp)
{
	if (!isatty(STDIN_FILENO))
		close_minishell(*msh, EXIT_FAILURE);
	init_all_null(&(*msh));
	//(*msh)->msh_pid = my_getpid(*msh); // needs 2 exit when activated
	copy_envp(*msh, envp);
//	if ((*msh)->debug_mode)
//		print_envp_in_struct(&(*msh)); //DEBUG TO DELETE
	prompt_and_read(&(*msh));
}


void	prompt_and_read(t_minishell **msh)
{
	char	*line;
	char	*prompt;
	int		exit_code;
	
	exit_code = 0;
	while (1)
	{
		prompt = get_prompt(exit_code);
		line = readline(prompt);
		free(prompt);
		add_history(line);
		(*msh)->token_list = NULL;
		(*msh)->promt_line = line;
	//	if (strncmp(line, "pwd", 3) == 0) // ???
	//		print_work_dir();
	//	if (strncmp(line, "env", 3) == 0) // ???
	//		print_env(msh);
	//	if (strncmp(line, "cd", 2) == 0) // ???
	//		ft_cd(msh);
	//	if (strncmp(line, "echo", 4) == 0) // ???
	//		ft_echo(msh);
		if (strncmp(line, "exit", 4) == 0) // ??
		{
			if (syntax_is_ok(&(*msh)))
				get_tokens(&(*msh), -1, '\0');
			ft_printf("exit\n");
			free(line);
			close_minishell(*msh, EXIT_SUCCESS);
		}
		if (syntax_is_ok(&(*msh)))
		{
			get_tokens(&(*msh), -1, '\0');
			if (!(*msh)->tree_root->left && !(*msh)->tree_root->right)
				exec_single_cmd(&(*msh));
			//else
			//	exec_tree(&(*msh));
		}
		free(line);
	}
}

//info --> create prompt wih current dir

char	*get_prompt(int	exit_code)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*final_prompt;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (ft_strdup("$ "));
	}
	prompt = ft_strjoin(cwd, " ");
	prompt = ft_strjoin(prompt, ft_itoa(exit_code));
	if (!prompt)
	{
		perror("ft_strjoin");
		return (ft_strdup("$ "));
	}
	final_prompt = ft_strjoin(prompt, " $ ");
	if (!final_prompt)
	{
		perror("ft_strjoin");
		return (ft_strdup("$ "));
	}
	return (final_prompt);
}
