/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_token_redir_l.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:07:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/18 16:02:39 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redir_l(t_msh **msh, int start)
{
	int			i;
	const char	*line;
	char		redir_hd[100];
	char		redir_in[100];

	i = start;
	line = (*msh)->prompt_line;
	if (line[i] && line[i + 1] == '<')
		i = tk_redir_hd(msh, line, redir_hd, i);
	else
		i = tk_redir_in(msh, line, redir_in, i);
	return (i);
}

int	tk_redir_hd(t_msh **msh, const char *line, char *redir_hd, int i)
{
	int			j;
	t_tk_lst	*new_tk;

	j = 0;
	while (line[i] && line[i] == '<')
	{
		redir_hd[j++] = line[i];
		i++;
	}
	redir_hd[j] = '\0';
	if (redir_hd[0] != '\0')
	{
		new_tk = safe_malloc(sizeof(t_tk_lst));
		app_tk(*msh, new_tk, redir_hd, REDIR_HD);
	}
	return (i - 1);
}

int	tk_redir_in(t_msh **msh, const char *line, char *redir_in, int i)
{
	int			j;
	t_tk_lst	*new_tk;

	j = 0;
	while (line[i] && line[i] == '<')
	{
		redir_in[j++] = line[i];
		i++;
	}
	redir_in[j] = '\0';
	if (redir_in[0] != '\0')
	{
		new_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk(*msh, new_tk, redir_in, REDIR_IN);
	}
	return (i - 1);
}
