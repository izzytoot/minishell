/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_syntax_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:01:56 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 14:10:16 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	conseq_operators_redir(const char *line)
{
	int		i;
	bool	in_quotes;

	i = -1;
	in_quotes = false;
	while (line[++i])
	{
		if (!line[i + 1])
			return (false);
		check_in_quotes(line[i], &in_quotes);
		if (line[i] && !in_quotes && ft_strchr(REDIR, line[i]))
		{
			if (line[i] == line[i + 1])
				i++;
			if (!line[i + 1])
				return (false);
			i++;
			while (line[i] && (ft_strchr(WS, line[i])))
				i++;
			if (line[i] == '<' || line[i] == '>')
				return (check_l_and_r(line, i));
		}
	}
	return (false);
}

bool	check_l_and_r(const char *line, int i)
{
	if (line[i] == '<')
		conseq_redir_l_case(line, i);
	else
		conseq_redir_r_case(line, i);
	return (true);
}

void	conseq_redir_r_case(const char *line, int i)
{
	if (line[i + 1] == '>')
		ft_putstr_fd(ERR_SYN_REDIR_APP, STDERR_FILENO);
	else
		ft_putstr_fd(ERR_SYN_REDIR_OUT, STDERR_FILENO);
}

void	conseq_redir_l_case(const char *line, int i)
{
	if (line[i + 1] == '<')
		ft_putstr_fd(ERR_SYN_REDIR_HD, STDERR_FILENO);
	else
		ft_putstr_fd(ERR_SYN_REDIR_IN, STDERR_FILENO);
}

bool	misplaced_redir_at_end(const char *line)
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
	else if (line[i] && !in_quotes && (line[i] == '|' && line[i - 1] == '>'))
		return (true);
	else if (line[i] && !in_quotes && ft_strchr(REDIR, line[i]))
		return (true);
	return (false);
}
