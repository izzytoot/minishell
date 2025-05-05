/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   64_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:50:08 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/05 14:35:54 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_msh **msh, t_tree_nd *node)
{
	int	status;
	
	status = 0;
	if (node->nb_arg > 1)
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
	t_ints		ints;
	t_flag_str	flags;
	t_quote		*quote_tmp;
	char		**new_args;

	init_aux_stucts(&flags, &ints, node);
	quote_tmp = node->quote_lst;
	new_args = ft_calloc((node->nb_arg + 1), sizeof(char *));
	while(ints.i < node->nb_arg)
	{
		if (!node->quote_lst->space_case && !flags.written)
			compose_arg(&ints, &flags, new_args, node);
		else if (node->quote_lst->space_case && !flags.space_prev)
			add_last(&ints, &flags, new_args, node);
		else
			lonely_arg(&ints, &flags, new_args, &node);
		if (flags.written)
			handle_written(&ints, &flags, &node);
	}
	new_args[ints.j] = NULL;
	node->quote_lst = quote_tmp;
//	free(quote_tmp); //check free
	return(new_args);
}
