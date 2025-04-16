/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   63_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:07 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/16 16:43:20 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		handle_hd(t_tree_node *node, int hd_fd)
{
	t_tree_node *current_node;
	char 		*eof;
	char		*new_line;

	current_node = node;
	eof = check_eof(current_node, current_node->file);
	while(1)
	{
		new_line = readline("> ");
		if (!new_line)
			break;
		if (ft_strcmp(new_line, eof) == 0)
		{
			free(new_line);
			break ;
		}
		ft_putstr_fd(new_line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(new_line);
		new_line = NULL;
	}
}
char	*check_eof(t_tree_node *node, char *file_name)
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
