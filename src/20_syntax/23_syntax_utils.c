/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:17:48 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/19 17:34:28 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../inc/minishell.h"

bool	look_for_pipe(const char *line, int i)
{
	i++;
	if (!line[i])
		return (false);
	while (line[i] && (ft_strchr(WHITESPACE, line[i]) || ft_strchr(QUOTE, line[i])))
		i++;
	if(line[i] == '|')
	{
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}	
	return (false);
}

void	conseq_redir_l_case(const char *line, int i)
{				
	if (line[i + 1] == '<')
		ft_putstr_fd(ERR_SYN_REDIR_HD, STDERR_FILENO);
	else
		ft_putstr_fd(ERR_SYN_REDIR_IN, STDERR_FILENO);
}

void	conseq_redir_r_case(const char *line, int i)
{
	if (line[i + 1] == '>')
		ft_putstr_fd(ERR_SYN_REDIR_APP, STDERR_FILENO);
	else
		ft_putstr_fd(ERR_SYN_REDIR_OUT, STDERR_FILENO);
}