/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   60_exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:24:34 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/05 16:55:50 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_tree(t_msh **msh, t_tree_nd *node)
{
	int	status;

	status = 0;
	expand_tree(msh, node);
	if(node->nb_arg > 1)
		node->args = remake_args(node);
	if ((*msh)->debug_mode && node->args) //TO DELETE
	{
		printf("------------------------------\n");
		printf(GR"new args are: "RES);
		int i = -1;
		while(node->args[++i])
			printf(BMAG"%s "RES, node->args[i]);
		printf("\n");
		printf("------------------------------\n");
	}
	expand_files(msh, node);
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
/*
char	*remake_fname(t_tree_nd *node)
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
*/