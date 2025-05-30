/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   63_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/30 17:30:19 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_heredocs(t_msh **msh, t_tree_nd *node)
{
	int			file_fd;
	static int	n;

	if (!node)
		return ;
	if (node->left)
		exec_heredocs(msh, node->left);
	if (node->right)
		exec_heredocs(msh, node->right);
	if (node->type == REDIR_HD)
	{
		node->tmp_file = ft_strjoin("/tmp/.heredoc_tmp", ft_itoa(n++));
//		node->tmp_file = ft_strjoin(ft_strdup("/tmp/.heredoc_tmp"),
//			ft_itoa(n++));
		file_fd = create_file_fd(node->type, node->tmp_file);
		if (file_fd < 0)
			exit_value(msh, 1, 1, 0);
		else
		{
			int pid = safe_fork(msh);
			int status = 0;
			if (pid == 0)
			{
				signal(SIGINT, signal_handles_hd);
				handle_hd(msh, node, file_fd);
			}
			else
			{
				signal(SIGINT, SIG_IGN);
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					status = WEXITSTATUS(status);
				printf("AQUI!!!!!!");
				exit_value(msh, status, 1, 0);
			}
			close(file_fd);
		}
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
		if (exit_value(NULL, 0, 0, 0) == -1)
			exit_value(msh, 130, 1, 1);
		if (!lines.new_l)
		{
			ft_dprintf(STDERR_FILENO, ERR_HD_EOF);
			ft_dprintf(STDERR_FILENO, "%s')\n", eof);
			exit_value(msh, 0, 1, 1);
		}
		if ((!eof && ft_strcmp(lines.new_l, "\0") == 0) || (ft_strcmp(lines.new_l, eof) == 0))
		{
			safe_free(lines.new_l);
			exit_value(msh, 0, 1, 1);
		}
		expand_line(msh, &lines, curr_nd, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		safe_free(lines.new_l);
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
