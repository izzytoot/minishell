/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   63_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/09 17:19:48 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_heredocs(t_msh **msh, t_tree_nd *node)
{
	int			file_fd;
	static int	n;

	if (!node)
		return ;
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
			handle_hd(msh, node, file_fd);
			close(file_fd);
		}
	}
	if (node->left)
		exec_heredocs(msh, node->left);
	if(node->right)
		exec_heredocs(msh, node->right);
}

void		handle_hd(t_msh **msh, t_tree_nd *node, int hd_fd)
{
	t_tree_nd 	*curr_nd;
	char 		*eof;
	t_hd_lines	lines;
	
	curr_nd = node;
	eof = check_eof(curr_nd, curr_nd->file);
	while(1)
	{
		lines.new_l = readline("> ");
		if (!lines.new_l)
			break;
		if (ft_strcmp(lines.new_l, eof) == 0)
		{
			free(lines.new_l);
			break;
		}
		expand_line(msh, &lines, curr_nd, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(lines.new_l);
		lines.new_l = NULL;
	}
}

char	*check_eof(t_tree_nd *node, char *file_name)
{
	int		i;
	char	*eof;
	
	i = 0;
	eof = NULL;
	if (!node->eof_ch && (file_name[i] == '-' || file_name[i] == '!'))
		eof = ft_substr(file_name, 1, (ft_strlen(file_name)));
	else
		eof = file_name;
//		eof = ft_strdup(file_name);
	return(eof);
}

