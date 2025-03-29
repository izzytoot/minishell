/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:26:11 by root              #+#    #+#             */
/*   Updated: 2025/03/29 16:44:16 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	syntax_is_ok(t_minishell **msh)
{
	const char *line;
	
	line = (*msh)->promt_line;
	if (unclosed_quotes(line)) //except if within quotes
		return (false);
	if (hd_open(line)) // << + word // para tirar
		return (false);
	if (misplaced_pipe(line)) // | at beginning or end
		return (false);
	if (conseq_operators_redir(line)) // redir + any redir
		return (false);
	if (misplaced_redir_hd(line)) // any redir + <<
		return (false);
	if (consec_operators_pipe(line)) // any oper + | //pipe + redir is ok (except << HD)
		return (false);
	if (misplaced_redir_at_end(line)) // < > << >> at the end
		return (false);
	if (unsupported_operators(line))
		return (false);
	else if (empty_quotes(line))
		return (false);
	return (true);
}

bool	hd_open(const char *line) 
{
	int		i;
	bool	in_quotes;
	
	i = -1;
	in_quotes = false;
	while (line[++i])
	{
		check_in_quotes(line[i], &in_quotes);
		if (line[i] && !in_quotes && line[i] == '<' && line[i + 1] == '<')
		{
			i = i + 2;
			while (line[i] && (ft_strchr(WHITESPACE, line[i])))
				i++;
			if (line[i] && !ft_strchr(OPERATOR, line[i]))
			{
				ft_putstr_fd(ERR_SYN_REDIR_HD_OPEN, STDERR_FILENO);
				return (true);
			}
		}
	}
	return(false);
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