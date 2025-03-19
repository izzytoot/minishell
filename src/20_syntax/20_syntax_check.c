/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:26:11 by root              #+#    #+#             */
/*   Updated: 2025/03/19 17:22:44 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	syntax_is_ok(t_minishell **msh)
{
	const char *line;
	
	line = (*msh)->promt_line;
	if (unclosed_sing_quotes(line))
		return (false);
	if (unclosed_doub_quotes(line))
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
	if (misplaced_redir_nl(line)) // < > << >> at the end
		return (false);
	else if (unsupported_operators(line))
		return (false);
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
			ft_putstr_fd(ERR_SYN_SQT, STDERR_FILENO);
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
			ft_putstr_fd(ERR_SYN_DQT, STDERR_FILENO);
			return (true);
		}
	}
	return (false);
}


bool	hd_open(const char *line) 
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i = i + 2;
			while (line[i] && (ft_strchr(WHITESPACE, line[i]) || ft_strchr(QUOTE, line[i])))
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
			if (ft_strchr("<", line[i]))
			{
				conseq_redir_r_case(line, i);
				return (true);
			}
			else if (ft_strchr(">", line[i]))
			{
				conseq_redir_r_case(line, i);
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
		{
			ft_putstr_fd(ERR_SYN_UNS_OP, STDERR_FILENO);
			return (true);
		}	
			
		if (line[i] == '&' && line[i + 1] == '&')
		{
			ft_putstr_fd(ERR_SYN_UNS_OP, STDERR_FILENO);
			return (true);
		}	
	}
	return (false);
}