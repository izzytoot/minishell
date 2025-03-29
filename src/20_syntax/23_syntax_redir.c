/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_syntax_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:01:56 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/29 14:37:25 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	conseq_operators_redir(const char *line)
{
	int		i;
	bool	in_quotes;

	i = -1;
	in_quotes = false;
	while(line[++i])
	{
		check_in_quotes(line[i], &in_quotes);
		if (line[i] && !in_quotes && ft_strchr(REDIR, line[i]))
		{
			if (line[i] == line[i + 1])
				i++;
			i++;
			while (line[i] && (ft_strchr(WHITESPACE, line[i])))
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

bool	misplaced_redir_hd(const char *line) 
{
	int	i;
	bool	in_quotes;
	
	i = 0;
	in_quotes = false;
	while (line[i] && (ft_strchr(WHITESPACE, line[i])))
		i++;
	if(ft_strchr(REDIR, line[i]) && (!ft_strchr(REDIR, line[i + 1]) || line[i] == line[i + 1]))
	{
		while(line[i])
		{
			check_in_quotes(line[i], &in_quotes);
			if (!in_quotes && line[i] == '<' && line[i + 1] == '<')
			{	
				ft_putstr_fd(ERR_SYN_REDIR_HD, STDERR_FILENO);
				return (true);
			}
			i++;
		}
	}
	return (false);
}

bool	misplaced_redir_at_end(const char *line) 
{
	int	len;
	int	i;
	bool	in_quotes;

	len = ft_strlen(line);
	i = len - 1;
	in_quotes = false;
	while(line[i] && (ft_strchr(WHITESPACE, line[i])))
		i--;
	check_in_quotes(line[i], &in_quotes);
	if (in_quotes)
		return (false);
	else if (line[i] && !in_quotes && ft_strchr(REDIR, line[i]))	
	{
		ft_putstr_fd(ERR_SYN_REDIR_NL, STDERR_FILENO);
		return (true);
	}
	return (false);
}