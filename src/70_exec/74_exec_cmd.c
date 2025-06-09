/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   74_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/09 18:20:38 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_msh **msh, t_tree_nd *node)
{
	int		status;

	status = 0;
	if (node->type == BT_CMD)
	{
		status = exec_bt_cmd(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	}
	else if (node->type == ENV_CMD)
	{
		if (node->cmd_content)
				ft_free_arrays((void **)node->cmd_content);
		node->cmd_content = join_cmd_and_args((node->cmd), node->args);
		status = exec_env_cmd(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	}
	else if (exec_sh_v(&(*msh), node) == 0)
		return (exit_value(msh, 0, 1, 0));
	return (output_cmd_errors(msh, node));
	// else if (node->type != ENV_CMD && (exec_sh_v(&(*msh), node) == 0))
	// 	return (exit_value(msh, 0, 1, 0));
	// pid = safe_fork(msh);
	// if (pid == 0)
	// 	exec_cmd_child(msh, node, &status);
	// exec_cmd_parent(pid, &status);
	// //return (output_cmd_errors(msh, node));
	// return (exit_value(msh, status, 1, 0));
}

int	exec_bt_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	if (ft_strcmp(node->cmd, "echo") == 0)
		status = ft_echo(&node);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		status = ft_cd(msh, &node);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(node->cmd, "export") == 0)
		status = ft_export(msh, &node, 0, 0);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		status = ft_unset(msh, &node);
	else if (ft_strcmp(node->cmd, "env") == 0)
		status = print_env(msh, &node);
	else if (ft_strcmp(node->cmd, "exit") == 0)
		status = ft_exit(msh, &node);
	else if (ft_strcmp(node->cmd, "''") == 0)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s", node->cmd, ERR_CNOTFOUND);
		status = 127;
	}
	return (exit_value(msh, status, 1, 0));
}

int	exec_env_cmd(t_msh **msh, t_tree_nd *node)
{
	int		pid;
	char	*path;
	int		status;
	int		sig;
	
	(void)sig;
	pid = safe_fork(msh);
	status = 0;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, sig_c_main);
		signal(SIGPIPE, sig_ig);
		status = choose_path(&(*msh), node, &path);
		if (status != 0)
			return (exit_value(msh, status, 1, 0));
		if(safe_execve(msh, path, node->cmd_content))
			return (exit_value(msh, status, 1, 1));
		return (exit_value(msh, status, 1, 1));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		waitpid(pid, &status, 0);
		signal(SIGINT, SIG_DFL);
		// if (WIFSIGNALED(status))
		// {
		// 	sig = WTERMSIG(status);
		// 	if (sig == SIGINT)
		// 	{
		// 		ft_putstr_fd("\n", 1);
		// 		return (exit_value(msh, 130, 1, 0));
		// 	}
		// 	else if (sig == SIGQUIT)
		// 	{
		// 		ft_putstr_fd("Quit (core dumped)\n", 1);
		// 		return (exit_value(msh, 131, 1, 0));
		// 	}
		// 	else if (WIFEXITED(status))
		// 		return (exit_value(msh, WEXITSTATUS(status), 1, 0));
		// 	else
		// 		return(0);
		// 	//signal(SIGINT, SIG_DFL);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			status = 130;
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			status = 130;
			write(1, "\n", 1);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 131)
		{
			status = 131;
			ft_printf("Quit (core dumped)\n");
		}
		else if(WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 0;
		}
	return (exit_value(msh, status, 1, 0));
}

int	exec_sh_v(t_msh **msh, t_tree_nd *node)
{
	int		status;
	int		i;
	char	**split;

	status = 0;
	i = 0;
	while (node->args[i])
	{
		if (check_shell_var(node->args[i]))
		{
			split = ft_split(node->args[i], '=');
			if (!split || !split[0])
				return (ft_free_arrays((void *)split), EXIT_FAILURE);
			if (update_var(&(*msh)->vars_list, split[0], split[1])
				!= EXIT_SUCCESS)
				return (ft_free_arrays((void *)split), EXIT_FAILURE);
			ft_free_arrays((void *)split);
		}
		i++;
	}
	if (!(*msh)->vars_list)
		return (-1);
	return (exit_value(msh, status, 1, 0));
}

int	safe_execve(t_msh **msh, char *path, char **argv)
{
	char	**envp_array;

	envp_array = cpy_for_execve(&(*msh));
	if (!envp_array)
		return (EXIT_FAILURE);
	if (execve(path, argv, envp_array) == -1)
	{
		// print_exec_error(argv[0]);
		perror("msh: execve:");
		ft_free_arrays((void **)envp_array);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
