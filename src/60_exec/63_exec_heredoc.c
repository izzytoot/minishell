/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   63_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/05 18:01:00 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_heredocs(t_msh **msh, t_tree_nd *node)
{
	int	file_fd;
	int 		status;

	status = 0;
	signal(SIGINT, SIG_DFL);
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
//	int			file_fd;
	static int	n;

	if (!node)
		exit (0);
	if (node->left)
		exec_files(msh, node->left);
	if (node->right)
		exec_files(msh, node->right);
	if (node->type == REDIR_HD)
	{
		node->tmp_file = ft_strjoin("/tmp/heredoc_tmp", ft_itoa(n++));
//		node->tmp_file = ft_strjoin(ft_strdup("/tmp/.heredoc_tmp"),
//			ft_itoa(n++));
	}
}

void	handle_hd(t_msh **msh, t_tree_nd *node, int hd_fd)
{
	t_tree_nd	*curr_nd;
	char		*eof;
	t_hd_lines	lines;

	curr_nd = node;
	eof = check_eof(curr_nd, curr_nd->file);
	while (1)
	{
		lines.new_l = readline("> ");
		if (!lines.new_l)
		{
			ft_dprintf(STDERR_FILENO, ERR_HD_EOF);
			ft_dprintf(STDERR_FILENO, "%s')\n", eof);
			lines.new_l = safe_free(lines.new_l);
			break ;
		}
		else if ((!eof && ft_strcmp(lines.new_l, "\0") == 0) || (ft_strcmp(lines.new_l, eof) == 0))
		{
			lines.new_l = safe_free(lines.new_l);
			exit_value(msh, 0, 1, 0);
			break ;
		}
		expand_line(msh, &lines, curr_nd, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		lines.new_l= safe_free(lines.new_l);
	}
}

char	*check_eof(t_tree_nd *node, char *file_name)
{
	int		i;
	char	*eof;

	i = 0;
	eof = ft_strdup("");
	if (!file_name)
		return (NULL);
	if (!node->eof_ch && (file_name[i] == '-' || file_name[i] == '!'))
		eof = ft_substr(file_name, 1, (ft_strlen(file_name)));
	else
		eof = ft_strdup(file_name);
	return (eof);
}
