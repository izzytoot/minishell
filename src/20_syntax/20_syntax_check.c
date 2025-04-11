/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:26:11 by root              #+#    #+#             */
/*   Updated: 2025/04/11 20:27:51 by icunha-t         ###   ########.fr       */
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
	if (misplaced_redir_at_end(line)) // < > << >> at the end
		return (false);
	if (unsupported_operators(line))
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