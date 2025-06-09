/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   70_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/09 20:36:14 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_tree(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	if (!node)
		return (exit_value(msh, 0, 0, 0));
	if (arg_expansions(node))
		expand_args(msh, node);
	if (node->nb_arg > 1 && arg_expansions(node))
		node->args = remake_args(node);
	if (type_is_word(&node->type) && !node->cmd
		&& ft_strchr(node->args[0], '/'))
		node->type = ENV_CMD;
	if ((*msh)->hd_check)
		status = deal_with_hd(msh, node, status);
	if ((*msh)->signal)
		return (exit_value(msh, 130, 1, 0));
	if (node->type == PIPE)
		status = exec_pipe(msh, node);
	else if (type_is_redir(&node->type))
		status = exec_redir_before_cmd(msh, node);
	else if (type_is_word(&node->type))
		deal_with_cmd(msh, node, &status);
	return (exit_value(msh, status, 1, 0));
}

char	**remake_args(t_tree_nd *node)
{
	t_ints		ints;
	t_flag_str	flags;
	t_quote		*quote_tmp;
	char		**new_args;
	char		**tmp_args;

	init_aux_structs(&flags, &ints, node);
	quote_tmp = node->quote_lst;
	tmp_args = node->args;
	new_args = ft_calloc((node->nb_arg + 1), sizeof(char *));
	while (ints.i < node->nb_arg)
	{
		if (!node->quote_lst->sp_case && !flags.written)
			compose_arg(&ints, &flags, new_args, node);
		else if (node->quote_lst->sp_case && !flags.space_prev)
			add_last(&ints, &flags, new_args, node);
		else
			lonely_arg(&ints, &flags, new_args, &node);
		if (flags.written)
			handle_written(&ints, &flags, &node);
	}
	new_args[ints.j] = NULL;
	node->quote_lst = quote_tmp;
	ft_free_arrays((void **)tmp_args);
	return (new_args);
}

int	deal_with_hd(t_msh **msh, t_tree_nd *node, int status)
{
	int	pid;

	(*msh)->hd_check = false;
	exec_files(msh, node);
	pid = safe_fork(msh);
	if (pid == 0)
	{
		get_msh(*msh, 0);
		exec_heredocs(msh, node);
		exit_value(msh, status, 1, 1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, sig_c_main);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			(*msh)->signal = true;
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			(*msh)->signal = true;
	}
	return (0);
}

void	sub_cmd(t_msh **msh, t_tree_nd *node, char ***new_args)
{
	char		*env_path;
	int			i;
	char		**sep_args;
	int			count;

	env_path = get_path((*msh)->envp_list);
	i = -1;
	count = 1;
	sep_args = ft_split((*new_args)[0], ' ');
	i = -1;
	while (sep_args[++i])
		count++;
	if (sep_args[0] && check_builtin(sep_args[0]))
		node->type = BT_CMD;
	else if (sep_args[0] && (check_env_cmd(sep_args[0], env_path, -1, 1)
			|| (ch_shlvl_bin(msh, sep_args[0]))))
		node->type = ENV_CMD;
	i = 0;
	if (node->type == BT_CMD || node->type == ENV_CMD)
		sub_cmd_util(node, sep_args, count, &new_args);
	ft_free_arrays((void **)sep_args);
}

void	sub_cmd_util(t_tree_nd *node, char **sep_args, int count,
			char ****new_args)
{
	char		**sep_args_tmp;
	char		**joinned_array;
	char		*tmp_cmd;

	sep_args_tmp = sep_args;
	tmp_cmd = NULL;
	joinned_array = NULL;
	if (node->cmd)
	{
		tmp_cmd = ft_strdup(node->cmd);
		node->cmd = safe_free(node->cmd);
	}
	node->cmd = ft_strdup(sep_args_tmp[0]);
	if (tmp_cmd)
	{
		sep_args_tmp[0] = safe_free(sep_args_tmp[0]);
		sep_args_tmp[0] = tmp_cmd;
	}
	if (count > 1)
	{
		joinned_array = get_joinned_array(tmp_cmd, sep_args, new_args);
		ft_free_arrays((void **)**new_args);
		(**new_args) = joinned_array;
	}
}
