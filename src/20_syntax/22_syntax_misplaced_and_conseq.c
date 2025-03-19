/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_syntax_misplaced_and_conseq.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:07:29 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/19 18:11:42 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	misplaced_pipe(const char *line)
{
	int	i;
	int	len;
	int	last;
	
	i = 0;
	len = ft_strlen(line);
	last = len - 1;
	while (line[i] && (ft_strchr(WHITESPACE, line[i]) || ft_strchr(QUOTE, line[i])))
		i++;
	if (line[i] && (ft_strchr("|", line[i])))
	{
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}
	while(line[last] && (ft_strchr(WHITESPACE, line[last]) || ft_strchr(QUOTE, line[last])))
		last--;
	if (line[last] && ft_strchr("|", line[last]))	
	{
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}
	return (false);
}
 
bool	misplaced_redir_nl(const char *line) 
{
	int	len;
	int	last;

	len = ft_strlen(line);
	last = len - 1;
	while(line[last] && (ft_strchr(WHITESPACE, line[last]) || ft_strchr(QUOTE, line[last])))
		last--;
	if (line[last] && ft_strchr(REDIR, line[last]))	
	{
		ft_putstr_fd(ERR_SYN_REDIR_NL, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	misplaced_redir_hd(const char *line) 
{
	int	i;

	i = -1;
	while (line[i] && (ft_strchr(WHITESPACE, line[i]) || ft_strchr(QUOTE, line[i])))
		i++;
	if(ft_strchr(REDIR, line[i]) && (!ft_strchr(REDIR, line[i + 1]) || line[i] == line[i + 1]))
	{
		while (!ft_strchr("<", line[i]))
			i++;
		if (line[i] == '<' && line[i + 1] == '<')
		{
			ft_putstr_fd(ERR_SYN_REDIR_HD, STDERR_FILENO);
			return (true);
		}
	}
	return (false);
}

bool	consec_operators_pipe(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] && ft_strchr(OPERATOR, line[i]))
		{
			if(ft_strchr("|", line[i]))
			{
				if (look_for_pipe(line, i))
					return (true);
			}	
			else if (ft_strchr(REDIR, line[i]))
			{
				if (line[i] == line[i + 1])
					i++;
				if (look_for_pipe(line, i))
					return (true);
			}
		}
	}
	return (false);
}

bool	conseq_operators_redir(const char *line)
{
	int		i;

	i = -1;
	while(line[++i])
	{
		if (line[i] && ft_strchr(REDIR, line[i]))
		{
			if (line[i] == line[i + 1])
				i++;
			i++;
			while (line[i] && (ft_strchr(WHITESPACE, line[i]) || ft_strchr(QUOTE, line[i])))
				i++;			
			if (line[i] == '<')
			{
				conseq_redir_l_case(line, i);
				return (true);
			}
			else if (line[i] == '>')
			{
				conseq_redir_r_case(line, i);
				return (true);
			}
		}
	}
	return (false);
}
