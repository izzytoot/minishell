/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:28:40 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/13 12:56:46 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		main(int ac, char **av, char **envp)
{
	t_minishell	*msh;
	
	
	msh = ft_calloc(1, sizeof(t_minishell));
	if (!msh)
		close_minishell(msh, RED ERR_MEM RES, EXIT_FAILURE);
	msh->active = true;
	prompt_loop(&(*msh));
	ft_init_msh(&(*msh), ac, av, envp);
	return(0);
}

void	prompt_loop(t_minishell *msh)
{
	char *line;
	char buffer[1024];
	int	i;
	
	msh->dir = getcwd(NULL, 1024); //perceber 1024
	i = 0;
	while ((line = readline("$ ")) != NULL)
	{
		strncpy(buffer, line, 1024);
		add_history(buffer);
		msh->promt_line = buffer;
		get_tokens(msh);
		if (strncmp(buffer, "pwd", 3) == 0)
			printf("%s\n", msh->dir);
		if (strncmp(buffer, "exit", 4) == 0)
		{
			ft_printf("exit\n");
			free(line);
			close_minishell(msh, NULL, EXIT_SUCCESS);
		}
		free(line);
	}
}

/*
int	main(void)
{	
	static char *buffer;
	int	fd;
	
	while(fd = open("console", O_RDONLY) >= 0) // console ???
	{
		if (fd >= 3)
		{
			close (fd);
			break ;
		}
	}
	while (get_command(buffer, sizeof(buffer)) >= 0)
	{
		if (buffer[0] == 'c' && buffer[1] == 'd' && buffer[2] == ' ')
		{
			buffer[ft_strlen(buffer) - 1] = 0; //cut \n
			if (cd_cmd(buffer + 3) < 0) // ptr to filename, if error
				ft_putstr_fd("Error changing to directory %s\n", buffer + 3);
			continue ;
		}
	}
	if (my_fork() == 0) //in CP returns 0, in PP returns PID of child
		run_cmd(parse_cmd(buffer));
	wait (0);
	exit (0);
	return(0);
}

int	my_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork error\n");
	return (pid);	
}

int	error_exit(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}
*/

/*
create get_cmd
create parse_cmd
create run_cmd
*/