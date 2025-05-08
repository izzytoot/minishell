/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/08 10:24:20 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;
	
	status = 0;
	if (node->type == BT_CMD)
	{
		status = exec_bt_cmd(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	}
	else if (node->type == ENV_CMD)
	{
		node->cmd_content = join_cmd_and_args(node->cmd, node->args);
		status = exec_env_cmd(&(*msh), node);
		return (exit_value(msh, status, 1, 0));
	}
	else if (exec_sh_v(&(*msh), node) == 0)
		return (exit_value(msh, 0, 1, 0));
	else
	{
		if (node->args[0][0] == '.' && node->args[0][1] == '/')
	 		ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_DIRNOTFOUND);
		else
			ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
		return (exit_value(msh, 127, 1, 0));
	}
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
				return(ft_free_arrays((void *)split), EXIT_FAILURE);
			if (update_var(&(*msh)->vars_list, split[0], split[1]) != EXIT_SUCCESS)
				return(ft_free_arrays((void *)split), EXIT_FAILURE);
			ft_free_arrays((void *)split);
		}
		i++;
	}
	if(!(*msh)->vars_list)
		return (-1);
	return (exit_value(msh, status, 1, 0));
}

int	exec_bt_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	if (ft_strcmp(node->cmd, "echo") == 0)
		status = ft_echo(&node); //returns exit code
	else if (ft_strcmp(node->cmd, "cd") == 0)
		status = ft_cd(msh, &node);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(node->cmd, "export") == 0)
		status = ft_export(msh, &node);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		status = ft_unset(msh, &node);
	else if (ft_strcmp(node->cmd, "env") == 0)
		status = print_env(msh, &node);
	else if (ft_strcmp(node->cmd, "exit") == 0)
		ft_exit(msh, &node); // tem que ser transformado em int
	return (exit_value(msh, status, 1, 0));
}

int	exec_env_cmd(t_msh **msh, t_tree_nd *node)
{
	pid_t	pid;
	char	*path;
	int		status;
	
	pid = safe_fork(msh);
	status = 0;
	if (pid == 0)
	{
		if (node->cmd && ft_strchr(node->cmd, '/'))
			update_shlvl(&(*msh)->envp_list);
		else
			path = check_env_cmd(node->cmd, get_path((*msh)->envp_list), -1);
		if (execve(path, node->cmd_content, (*msh)->envp) == -1)
			perror("msh: execve: "); // check pre-error message
	}
	else
	{
		waitpid(pid, &status, 0); //wait for exit code from child
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	return (exit_value(msh, status, 1, 0));
}

void	update_shlvl(t_list **env_list)
{
	char    *shlvl_value;
	char    *shlvl_str;
    int     shlvl;
	
	shlvl_value = get_var_val(*env_list, "SHLVL");
	if (shlvl_value)
    {
		shlvl = ft_atoi(shlvl_value);
        shlvl++;
		shlvl_str = ft_itoa(shlvl);
		if (!shlvl_str)
			return ;
		update_var(env_list, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
	else
		update_var(env_list, "SHLVL", "1");
}
