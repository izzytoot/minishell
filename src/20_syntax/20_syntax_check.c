/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:26:11 by root              #+#    #+#             */
/*   Updated: 2025/05/02 16:54:43 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	syntax_is_ok(t_msh **msh)
{
	const char	*line;
	int			hd_index;

	line = (*msh)->prompt_line;
	hd_index = check_if_hd(line);
	if (any_of_these_syn(line))
		return (exit_value(msh, 2, 1, 0));
	if (hd_index >= 0)
	{
		if (misplaced_redir_at_end(line))
		{
			exec_fake_hd(line, hd_index);
			ft_putstr_fd(ERR_SYN_REDIR_NL, STDERR_FILENO);
			return (exit_value(msh, 2, 1, 0));
		}
	}
	else
	{
		if (misplaced_redir_at_end(line))
		{
			ft_putstr_fd(ERR_SYN_REDIR_NL, STDERR_FILENO);
			return (exit_value(msh, 2, 1, 0));
		}
	}
	return (0);
}

bool	any_of_these_syn(const char *line)
{
	if (unclosed_quotes(line))
		return (true);
	if (misplaced_pipe(line))
		return (true);
	if (conseq_operators_redir(line))
		return (true);
	if (consec_operators_pipe(line))
		return (true);
	if (unsupported_operators(line))
		return (true);
	return (false);
}

bool	unsupported_operators(const char *line)
{
	int		i;
	bool	in_quotes;

	i = -1;
	in_quotes = false;
	while (line[++i])
	{
		check_in_quotes(line[i], &in_quotes);
		if (!in_quotes && (line[i] == '|' && line[i + 1] == '|'))
		{
			ft_putstr_fd(ERR_SYN_UNS_OP, STDERR_FILENO);
			return (true);
		}
		if (!in_quotes && (line[i] == '&' && line[i + 1] == '&'))
		{
			ft_putstr_fd(ERR_SYN_UNS_OP, STDERR_FILENO);
			return (true);
		}
	}
	return (false);
}

void	exec_fake_hd(const char *line, int hd_index)
{
	char	*eof;
	char	*new_line;
	int		fd;

	eof = get_eof(line, hd_index);
	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0600);
	while (1)
	{
		new_line = readline("> ");
		if (!new_line)
			break ;
		if (ft_strcmp(new_line, eof) == 0)
		{
			free(new_line);
			break ;
		}
		ft_putstr_fd(new_line, fd);
		free(new_line);
		new_line = NULL;
	}
}
