/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/22 15:23:51 by icunha-t         ###   ########.fr       */
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
		node->args = remake_args(msh, node);
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
		status = exec_cmd(msh, node);
	return (exit_value(msh, status, 1, 0));
}

char	**remake_args(t_msh **msh, t_tree_nd *node)
{
	t_ints		ints;
	t_flag_str	flags;
	t_quote		*quote_tmp; //don´t think we use this again. Check to del and reduce lines
	char		**new_args;

	init_aux_structs(&flags, &ints, node);
	quote_tmp = node->quote_lst; //don´t think we use this again. Check to del and reduce lines
	new_args = ft_calloc((node->nb_arg + 1), sizeof(char *));
//	if (!node->cmd && !node->quote_lst->sp_case)
//		node->quote_lst->sp_case = true;
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
	node->quote_lst = quote_tmp; //don´t think we use this again. Check to del and educe lines
	if (!node->cmd && new_args[0])
		sub_cmd(msh, node, &new_args);
	return (new_args);
}

void	sub_cmd(t_msh **msh, t_tree_nd *node, char ***new_args)
{
	char		*env_path;

	env_path = get_path((*msh)->envp_list);
	if (check_builtin((*new_args)[0]))
		node->type = BT_CMD;
	else if (check_env_cmd((*new_args)[0], env_path, -1) || (ch_shlvl((*new_args)[0])))
		node->type = ENV_CMD;
	if (node->type == BT_CMD || node->type == ENV_CMD)
	{
		node->cmd = ft_strdup((*new_args)[0]);
		(*new_args) = ft_array_dup(++(*new_args));	
	}
}