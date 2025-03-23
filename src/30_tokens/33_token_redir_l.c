/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_token_redir_l.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:07:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/23 18:24:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redir_l(t_minishell **msh, int start)
{
	int			i;
	const char *line;
	char		redir_hd[100];
	char		redir_in[100];
	
	i = start;
	line = (*msh)->promt_line;
	if (line[i] && line[i + 1] == '<')
		i = token_is_redir_hd(msh, line, redir_hd, i);
	else
		i = token_is_redir_in(msh, line, redir_in, i);
	return(i);
}

int	token_is_redir_hd(t_minishell **msh, const char *line, char *redir_hd, int i)
{
	int		j;
	t_token_lst	*new_token;
	
	j = 0;
	while(line[i] && line[i] == '<')
	{
		redir_hd[j++] = line[i];
		i++;
	}
	redir_hd[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, redir_hd, REDIR_HD);
	return (i - 1);
}

int	token_is_redir_in(t_minishell **msh, const char *line, char *redir_in, int i)
{
	int		j;
	t_token_lst	*new_token;
	
	j = 0;
	while(line[i] && line[i] == '<')
	{
		redir_in[j++] = line[i];
		i++;
	}
	redir_in[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, redir_in, REDIR_IN);
	return (i - 1);
}