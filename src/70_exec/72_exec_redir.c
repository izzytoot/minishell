/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   72_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:20 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 16:02:07 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_redir_before_cmd(t_msh **msh, t_tree_nd *node)
{
	t_redir_data	redir_data;
	t_tree_nd		*redir_nodes[32];
	t_tree_nd		*curr_node;
	int				i;
	int				status;

	curr_node = node;
	status = 0;
	init_str_reset_std(msh, &redir_data, 1);
	i = collect_redirs_and_cmd(msh, &curr_node, redir_nodes, &redir_data);
	while (--i >= 0)
	{
		status = exec_redir(msh, redir_nodes[i]);
		if (status != 0)
		{
			init_str_reset_std(msh, &redir_data, 2);
			return (exit_value(msh, status, 1, 0));
		}
	}
	if (redir_data.cmd_nd)
		status = exec_tree(msh, redir_data.cmd_nd);
	init_str_reset_std(msh, &redir_data, 2);
	return (exit_value(msh, status, 1, 0));
}

int	collect_redirs_and_cmd(t_msh **msh, t_tree_nd **curr_nd,
		t_tree_nd **redir_nd, t_redir_data *redir_data)
{
	int	i;

	i = 0;
	while (*curr_nd && type_is_redir(&(*curr_nd)->type))
	{
		redir_nd[i] = *curr_nd;
		if (((*curr_nd)->type == REDIR_IN || (*curr_nd)->type == REDIR_HD)
			&& redir_data->orig_stdin == -1)
			redir_data->orig_stdin = safe_dup(msh, (*curr_nd)->fd);
		if (((*curr_nd)->type == REDIR_OUT || (*curr_nd)->type == REDIR_APP)
			&& redir_data->orig_stdout == -1)
			redir_data->orig_stdout = safe_dup(msh, (*curr_nd)->fd);
		if ((*curr_nd)->right && type_is_word(&(*curr_nd)->right->type))
			redir_data->cmd_nd = (*curr_nd)->right;
		else if ((*curr_nd)->left && type_is_word(&(*curr_nd)->left->type))
			redir_data->cmd_nd = (*curr_nd)->left;
		*curr_nd = (*curr_nd)->left;
		i++;
	}
	return (i);
}

int	exec_redir(t_msh **msh, t_tree_nd *node)
{
	int		file_fd;

	file_fd = -1;
	if (!node->file || node->ch_ambg)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s", (*msh)->tmp_fname,
			ERR_AMBREDIR);
		return (exit_value(msh, 1, 1, 0));
	}
	if (node->type != REDIR_HD)
		file_fd = create_file_fd(node->type, node->file);
	else
		file_fd = open(node->tmp_file, O_RDONLY);
	if (file_fd < 0)
		return (exit_value(msh, 1, 1, 0));
	if (node->type == REDIR_HD)
		safe_dup2(msh, file_fd, STDIN_FILENO);
	else
		safe_dup2(msh, file_fd, node->fd);
	close(file_fd);
	return (exit_value(msh, 0, 1, 0));
}

int	create_file_fd(t_tk_type type, char *file_name)
{
	int	file_fd;

	if (type == REDIR_IN)
		file_fd = open(file_name, O_RDONLY);
	else if (type == REDIR_OUT)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APP)
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_HD)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0600);
	else
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s\n", ERR_UNKRED, strerror(errno));
		return (-1);
	}
	if (file_fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "msh: %s: %s\n", file_name, strerror(errno));
		return (-1);
	}
	return (file_fd);
}

void	init_str_reset_std(t_msh **msh, t_redir_data *redir_data, int n)
{
	if (n == 1)
	{
		redir_data->cmd_nd = NULL;
		redir_data->orig_stdin = -1;
		redir_data->orig_stdout = -1;
	}
	if (n == 2)
	{
		if (redir_data->orig_stdin != -1)
			safe_dup2(msh, redir_data->orig_stdin, 0);
		if (redir_data->orig_stdout != -1)
			safe_dup2(msh, redir_data->orig_stdout, 1);
	}
}
