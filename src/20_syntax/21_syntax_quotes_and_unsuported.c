/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_syntax_quotes_and_unsuported.c.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:05:45 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/19 18:11:12 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

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
