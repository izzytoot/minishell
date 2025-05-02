/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/02 18:30:54 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;
	
	status = 0;
	node->args = remake_args(node);
	int i = 0;
	while(node->args[i])
	{
		printf("arg %d is %s\n", i, node->args[i]);
		i++;
	}
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
	else
	{
		ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
		return (exit_value(msh, 127, 1, 0));
	}
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
	//else if (ft_strcmp(node->cmd, "export") == 0)
	//	return (ft_export(&(*msh)));
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
		////se path comeca com ./, isso é o path
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

char	**remake_args(t_tree_nd *node)
{
	int		i;
	int		j;
	t_quote	*quote_tmp;
	char	**new_args;
	bool	flag;
	
	i = 0;
	j = 0;
	quote_tmp = node->quote_lst;
	flag = false;
	new_args = ft_calloc(node->nb_arg, sizeof(char *));
	while(node->args[i])
	{
		if (!node->quote_lst->space_case && node->quote_lst->next && node->args[i + 1] && !flag)
		{
			new_args[j] = ft_strdup(ft_strjoin(node->args[i], node->args[i + 1]));
			flag = true;
			j++;
			i++;
			node->quote_lst = node->quote_lst->next;
		}
		else if (!node->quote_lst->space_case && node->args[i + 1] && flag)
		{
			i++;
			if (node->quote_lst->next)
				node->quote_lst = node->quote_lst->next;
		}
		else // repeating last arg
		{
			new_args[j] = ft_strdup(node->args[i]);
			j++;
			i++;
			if (node->quote_lst->next)
				node->quote_lst = node->quote_lst->next;
		}
	}
	node->quote_lst = quote_tmp;
	free(quote_tmp); //check free
	return(new_args);
}
