/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_syntax_quotes_and_unsuported.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:05:45 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/21 15:18:34 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	empty_quotes(const char *line)
{
	int	i;
	
	i = -1;
	while(line[++i])
	{
		if (ft_strchr(QUOTE, line[i]) && line[i + 1] == line[i])
		{
			ft_putstr_fd(ERR_SYN_EMPT, STDERR_FILENO);
			return (true);
		}
	}
	return (false);
}

bool	unclosed_quotes(const char *line)
{
	int	i;
	bool in_quotes = false;
	char quote_char = '\0';

	i = 0;
    while (line[i])
    {
		check_in_quotes(line[i], &in_quotes);
        i++;
    }
	if(in_quotes)
	{
		if (quote_char == '\'')
			ft_putstr_fd(ERR_SYN_SQT, STDERR_FILENO);
		else if (quote_char == '\"')
			ft_putstr_fd(ERR_SYN_DQT, STDERR_FILENO);
	}
    return (in_quotes);
}

bool	unclosed_sing_quotes_1(const char *line)
{
	const char *ptr = line;
	
	while((ptr = ft_strchr(ptr, '\'')))
	{
		ptr = ft_strchr(ptr + 1, '\'');
		if (!ptr)
		{
			ft_putstr_fd(ERR_SYN_SQT, STDERR_FILENO);
			return (true);
		}
		ptr++;
	}
	return (false);
}

bool	unclosed_doub_quotes(const char *line)
{
	const char *ptr = line;
	
	while((ptr = ft_strchr(ptr, '\"')))
	{
		ptr = ft_strchr(ptr + 1, '\"');
		if (!ptr)
		{
			ft_putstr_fd(ERR_SYN_DQT, STDERR_FILENO);
			return (true);
		}
		ptr++;
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
