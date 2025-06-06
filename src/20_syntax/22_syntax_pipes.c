/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_syntax_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:07:29 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 14:09:34 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	misplaced_pipe(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (ft_strchr(WS, line[i])))
		i++;
	if (pipe_at_beginning(line))
		return (true);
	else if (pipe_at_end(line))
		return (true);
	return (false);
}

bool	pipe_at_beginning(const char *line)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (line[i] && (ft_strchr(WS, line[i])))
		i++;
	check_in_quotes(line[i], &in_quotes);
	if (in_quotes)
		return (false);
	else if (line[i] && !in_quotes && (ft_strchr("|", line[i])))
	{
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	pipe_at_end(const char *line)
{
	int		len;
	int		i;
	bool	in_quotes;

	len = ft_strlen(line);
	i = len - 1;
	in_quotes = false;
	while (line[i] && (ft_strchr(WS, line[i])))
		i--;
	check_in_quotes(line[i], &in_quotes);
	if (in_quotes)
		return (false);
	else if (line[i] && !in_quotes && (ft_strchr("|", line[i])))
	{
		if (line[i - 1] == '>' || line[i - 1] == '|')
			return (false);
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	consec_operators_pipe(const char *line)
{
	int		i;
	bool	in_quotes;

	i = -1;
	in_quotes = false;
	while (line[++i])
	{
		check_in_quotes(line[i], &in_quotes);
		if (line[i] && !in_quotes && ft_strchr(OPERATOR, line[i]))
		{
			if (ft_strchr("|", line[i]) && !ft_strchr("|", line[i + 1]))
			{
				if (line[i + 1] != '\0' && look_for_pipe(line, i))
					return (true);
			}
			else if (ft_strchr(REDIR, line[i]))
			{
				if (line[i] == line[i + 1])
					i++;
				if (line[i + 1] != '\0' && look_for_pipe(line, i))
					return (true);
			}
		}
	}
	return (false);
}
