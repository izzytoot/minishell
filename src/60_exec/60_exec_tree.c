/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/26 18:23:24 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_tree(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	if (!node)
		return (exit_value(msh, 0, 0, 0)); //changed exit status from 2 to 0
	expand_args(msh, node);
	if (node->nb_arg > 1)
		node->args = remake_args(node);
	if (type_is_word(&node->type) && !node->cmd
		&& ft_strchr(node->args[0], '/'))
		node->type = ENV_CMD;
	if ((*msh)->debug_mode && node->args) //TO DELETE
	{
		printf("------------------------------\n");
		printf(GR"new args are: "RES);
		int	i = -1;
		while (node->args[++i])
			printf(BMAG"%s "RES, node->args[i]);
		printf("\n");
		printf("------------------------------\n");
	}
	if ((*msh)->hd_check)
	{
		exec_heredocs(msh, node);
		(*msh)->hd_check = false;
	}
	if (node->type == PIPE)
		status = exec_pipe(msh, node);
	else if (type_is_redir(&node->type))
		status = exec_redir_before_cmd(msh, node);
	else if (type_is_word(&node->type))
	{
		if (ch_if_sub_cmd(node))
			sub_cmd(msh, node, &node->args);
		status = exec_cmd(msh, node);
	}
	return (exit_value(msh, status, 1, 0));
}

char	**remake_args(t_tree_nd *node)
{
	t_ints		ints;
	t_flag_str	flags;
	t_quote		*quote_tmp;
	char		**new_args;

	init_aux_structs(&flags, &ints, node);
	quote_tmp = node->quote_lst;
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
	return (new_args);
}

bool	ch_if_sub_cmd(t_tree_nd *node)
{
	if (node->cmd || !node->args[0])
		return (false);
	if ((ft_strcmp(node->args[0], ".") == 0)
		|| (ft_strcmp(node->args[0], "..") == 0))
		return (false);
	if (!node->cmd && node->args[0])
		return (true);
	return (false);
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
	while (sep_args[++i])
		count++;
	if (check_builtin(sep_args[0]))
		node->type = BT_CMD;
	else if (check_env_cmd(sep_args[0], env_path, -1)
		|| (ch_shlvl(msh, sep_args[0])))
		node->type = ENV_CMD;
	i = 0;
	if (node->type == BT_CMD || node->type == ENV_CMD)
	{
		node->cmd = ft_strdup(sep_args[0]);
		if (count > 1)
			(*new_args) = ft_array_join((ft_array_dup(++sep_args)),
					(ft_array_dup(++(*new_args))));
	}
}

int	output_cmd_errors(t_msh **msh, t_tree_nd *node)
{
	if (node->type == ARG && !node->args[0])
		return (exit_value(msh, 0, 1, 0));
	else if (node->type == ARG && (ft_strcmp(".", node->args[0]) == 0))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_PT);
		return (exit_value(msh, 2, 1, 0));
	}
	ft_dprintf(STDERR_FILENO, "%s: %s", node->args[0], ERR_CNOTFOUND);
	return (exit_value(msh, 127, 1, 0));
}
