/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   63_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/07 16:23:40 by isabel           ###   ########.fr       */
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
		node->tmp_file = ft_strjoin(ft_strdup("/tmp/.heredoc_tmp"),
			ft_itoa(n++));
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
		eof = ft_strdup(file_name);
	return(eof);
}

void	expand_line(t_msh **msh, t_hd_lines *lines,
	t_tree_nd *curr_nd, int hd_fd)
{
	int 	i;

	i = 0;
	if (!curr_nd->exp_hd || !count_exp(lines->new_l, 0)) 
		ft_putstr_fd(lines->new_l, hd_fd);
	else
	{
		lines->exp_newl = ft_split(lines->new_l, ' ');
		while (lines->exp_newl[i])
		{
			if (count_exp(lines->exp_newl[i], 0))
				lines->exp_newl[i] = expand_word(msh, lines->exp_newl[i]);
			i++;
		}
		ft_putstr_fd(ft_unsplit(lines->exp_newl), hd_fd);
	}
}

char	*expand_word(t_msh **msh, char *word)
{
	char	*pre_c;
	char	**kw;
	char	*post_c;
	char	*new_c;
	int 	i;

	ft_init_var((void **)&pre_c, (void **)&kw,
		(void **)&post_c, (void **)&new_c);
	i = 0;
	if (word)
	{
		pre_c = get_pre_cont(word, &i);
		kw = build_kw_array(word, &i);
		post_c = get_post_cont(word, &i);
		new_c = build_new_arg(msh, kw);
		subst_arg(&word, pre_c, new_c, post_c);
	}
	else
		return (NULL);
	return (word);
}
