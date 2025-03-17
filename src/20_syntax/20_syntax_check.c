/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:26:11 by root              #+#    #+#             */
/*   Updated: 2025/03/17 18:15:34 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	syntax_is_ok(t_minishell **msh)
{
	const char *line;
	
	line = (*msh)->promt_line;
	if (unclosed_sing_quotes(line))
		ft_putstr_fd(ERR_SYN_QT, STDERR_FILENO);
	if (unclosed_doub_quotes(line))
		ft_putstr_fd(ERR_SYN_QT, STDERR_FILENO);
	if (misplaced_operators(line))
		ft_putstr_fd(ERR_SYN_MS_OP, STDERR_FILENO);
	else if (unsupported_operators(line))
		ft_putstr_fd(ERR_SYN_UNS_OP, STDERR_FILENO);
	return (true);
}

bool	unclosed_sing_quotes(const char *line)
{
	int	i;
	int	j;
	
	i = -1;
	while(line[++i])
	{
		if (line[i] == '\'')
		{
			j = i;
			while (line[j])
			{
				if (line[++j] == '\'')
					return (false);
			}
			return (true);
		}
	}
	return (false);
}

bool	unclosed_doub_quotes(const char *line)
{
	int	i;
	int	j;
	
	i = -1;
	while(line[++i])
	{
		if (line[i] == '\"')
		{
			j = i;
			while (line[j])
			{
				if (line[++j] == '\"')
					return (false);
			}
			return (true);
		}
	}
	return (false);
}

bool	misplaced_operators(const char *line)
{
	int	i;
	int	len;
	int	last;
	
	i = 0;
	len = ft_strlen(line);
	last = len - 1;
	while (line[i] && (ft_strchr(WHITESPACE, line[i]) || ft_strchr(QUOTE, line[i])))
		i++;
	if (line[i] && (ft_strchr("|", line[i]) || (line[i] == '<' && line[i + 1] == '<')))
		return (true);
	while(line[last] && (ft_strchr(WHITESPACE, line[last]) || ft_strchr(QUOTE, line[last])))
		last--;;
	if (line[i] && ft_strchr(OPERATOR, line[last]))	
		return (true);
	return (false);
}

bool	conseq_operators(const char *line)
{
	int		i;

	i = -1;
	while(line[++i])
	{
		if (ft_strchr(OPERATOR, line[i]))
		{
			if (line[i] != '|' || (line[i] == '|' && line[i + 1] != '|'))
			{
				while (line[i] && ft_strchr(WHITESPACE, line[i]))
					i++;
				if (line[i] && ft_strchr(OPERATOR, line[i]))
					return (true);
			}
		}
	}
	return (false);	
}

bool	unsupported_operators(const char *line)
{
	int		i;

	i = -1;
	while(line[++i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			return (true);
		if (line[i] == '&' && line[i + 1] == '&')
			return (true);
	}
	return (false);
}