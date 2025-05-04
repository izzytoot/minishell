/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/04 23:09:16 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;
	
	status = 0;
	node->args = remake_args(node);
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
	bool	flag_wr;
	bool	flag_space_prev;
	bool	flag_space_next;
	
	i = 0;
	j = 0;
	if (node->nb_arg <= 1)
		return (node->args);
	quote_tmp = node->quote_lst;
	flag_wr = false;
	flag_space_prev = true;
	flag_space_next = node->quote_lst->space_case;
	new_args = ft_calloc(node->nb_arg, sizeof(char *));
	while(i < node->nb_arg)
	{
		if (!node->quote_lst->space_case && !flag_wr)
		{
			if (j == 0 || ((flag_space_next || flag_space_prev) && node->args[i + 1])) //first of group
			{
				new_args[j] = ft_strdup(ft_strjoin(node->args[i], node->args[i + 1]));
				i++;
				if (node->quote_lst->next)
					node->quote_lst = node->quote_lst->next;
			}
			else //any other of group
			{
				if (!flag_space_prev)
				{
					j--;
					new_args[j] = ft_strdup(ft_strjoin(new_args[j], node->args[i]));
				}
				else //last arg when lonely (!space_case)
					new_args[j] = ft_strdup(node->args[i]); //not sure I need this
			}
			flag_wr = true;
			flag_space_prev = false;
			j++;
		}
		else if (node->quote_lst->space_case && !flag_space_prev) // last of group
		{
			j--;
			new_args[j] = ft_strdup(ft_strjoin(new_args[j], node->args[i]));
			flag_wr = true;
			flag_space_prev = true;
			j++;
		}
		else //lonely arg
		{
			new_args[j] = ft_strdup(node->args[i]);
			j++;
			i++;
			if (node->quote_lst->next)
				node->quote_lst = node->quote_lst->next;
			flag_wr = false;
			flag_space_prev = true;
		}
		if (flag_wr) //skipped arg when joined earlier
		{
			i++;
			if (!node->quote_lst->space_case)
				flag_space_next = false;
			else
				flag_space_next = true;
			if (node->quote_lst->next)
				node->quote_lst = node->quote_lst->next;
			flag_wr = false;
		}
	}
	node->quote_lst = quote_tmp;
//	free(quote_tmp); //check free
	return(new_args);
}
