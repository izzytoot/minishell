/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:26:11 by root              #+#    #+#             */
/*   Updated: 2025/04/11 21:02:32 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	syntax_is_ok(t_minishell **msh)
{
	const char *line;
	int			hd_index;
	
	line = (*msh)->prompt_line;
	hd_index = check_if_hd(line);
	
	if (unclosed_quotes(line)) //except if within quotes
		return (false);
	if (misplaced_pipe(line)) // | at beginning or end
		return (false);
	if (conseq_operators_redir(line), hd_index) // redir + any redir
		return (false);
	if (consec_operators_pipe(line)) // any oper + | //pipe + redir is ok (except << HD)
		return (false);
	if (unsupported_operators(line))
		return (false);
	// if (hd_index >= 0) //THIS ONLY HAPPENS IF THERE IS A SYNTAX ERROR
	// 	exec_fake_hd(line, hd_index);
	if (misplaced_redir_at_end(line)) // < > << >> at the end
		return (false);
	return (true);
}

bool	unsupported_operators(const char *line)
{
	int		i;
	bool	in_quotes;

	i = -1;
	in_quotes = false;
	while(line[++i])
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
	int		i;
	int		fd;
	int	size;
	int	eof_s;
	
	hd_index++; // second <
	i = 0;
	size = 0;
	if (line[hd_index + 1] == ' ')
		hd_index++;
	hd_index++;
	eof_s = hd_index;
	while(!ft_strchr(WHITESPACE, line[++hd_index]))
		size++;
	eof = malloc(sizeof(char) * (size + 1));
	while(!ft_strchr(WHITESPACE, line[eof_s]))
	{
		eof[i] = line[eof_s];
		eof_s++;
		i++;
	}
	eof[i] = '\0';
	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0600);
	while (1)
	{
		new_line = readline("> ");
		if (!new_line)
			break;
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
