/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   73_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/07 15:39:04 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_heredocs(t_msh **msh, t_tree_nd *node)
{
	int	file_fd;

	signal(SIGINT, ctrl_c_hd);
	if (!node)
		exit (0);
	if (node->left)
		exec_heredocs(msh, node->left);
	if (node->right)
		exec_heredocs(msh, node->right);
	if (node->type == REDIR_HD)
	{
		file_fd = open(node->tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (file_fd < 0)
			exit_value(msh, 1, 1, 1);
		handle_hd(msh, node, file_fd);
		close(file_fd);
	}
}

void	exec_files(t_msh **msh, t_tree_nd *node)
{
	static int	n;
	char		*nb;

	if (!node)
		exit (0);
	if (node->left)
		exec_files(msh, node->left);
	if (node->right)
		exec_files(msh, node->right);
	if (node->type == REDIR_HD)
	{
		nb = ft_itoa(n++);
		node->tmp_file = ft_strjoin("/tmp/heredoc_tmp", nb);
		nb = safe_free(nb);
	}
}

void	handle_hd(t_msh **msh, t_tree_nd *node, int hd_fd)
{
	t_tree_nd	*curr_nd;
	t_hd_lines	lines;

	curr_nd = node;
	node->eof = check_eof(curr_nd, curr_nd->file);
	while (1)
	{
		lines.ch_exp = false;
		lines.new_l = readline("> ");
		if (!lines.new_l)
		{
			ctrl_d_error(node->eof);
			lines.new_l = safe_free(lines.new_l);
			break ;
		}
		if ((!node->eof && ft_strcmp(lines.new_l, "\0") == 0)
			|| (ft_strcmp(lines.new_l, node->eof) == 0))
		{
			lines.new_l = safe_free(lines.new_l);
			break ;
		}
		save_lines(msh, lines, curr_nd, hd_fd);
	}
	node->eof = safe_free(node->eof);
}

void	save_lines(t_msh **msh, t_hd_lines lines, t_tree_nd *curr_nd, int hd_fd)
{
	expand_line(msh, &lines, curr_nd, hd_fd);
	ft_putstr_fd("\n", hd_fd);
	lines.new_l = safe_free(lines.new_l);
	if (lines.ch_exp)
		ft_free_arrays((void **)lines.exp_newl);
}

char	*check_eof(t_tree_nd *node, char *file_name)
{
	int		i;
	char	*eof;

	i = 0;
	eof = ft_strdup("");
	if (!file_name)
	{
		eof = safe_free(eof);
		return (NULL);
	}
	if (!node->eof_ch && (file_name[i] == '-' || file_name[i] == '!'))
	{
		eof = safe_free(eof);
		eof = ft_substr(file_name, 1, (ft_strlen(file_name)));
	}
	else
	{
		eof = safe_free(eof);
		eof = ft_strdup(file_name);
	}
	return (eof);
}
