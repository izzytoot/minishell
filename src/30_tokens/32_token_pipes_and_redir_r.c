/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32_token_pipes_and_redir_r.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:20:33 by root              #+#    #+#             */
/*   Updated: 2025/05/22 00:41:13 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	tk_pipe(t_msh **msh, int start)
{
	int			i;
	int			j;
	char		pipe[5];
	t_tk_lst	*new_tk;
	const char	*line;

	i = start;
	j = 0;
	line = (*msh)->prompt_line;
	while (line[i] && line[i] == '|')
	{
		pipe[j++] = line[i];
		i++;
	}
	pipe[j] = '\0';
	if (pipe[0] != '\0')
	{
		new_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk(*msh, new_tk, pipe, PIPE);
		i = empty_case(msh, line, i, true);
	}
	return (i - 1);
}

int	redir_r(t_msh **msh, int start)
{
	int			i;
	const char	*line;
	char		redir_app[5];
	char		redir_out[5];

	i = start;
	line = (*msh)->prompt_line;
	if (line[i] && line[i + 1] == '>')
		i = tk_redir_app(msh, line, redir_app, i);
	else
		i = tk_redir_out(msh, line, redir_out, i);
	return (i);
}

int	tk_redir_app(t_msh **msh, const char *line, char *redir_app, int i)
{
	int			j;
	t_tk_lst	*new_tk;

	j = 0;
	while (line[i] && line[i] == '>')
	{
		redir_app[j++] = line[i];
		i++;
	}
	redir_app[j] = '\0';
	if (redir_app[0] != '\0')
	{
		new_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk(*msh, new_tk, redir_app, REDIR_APP);
	}
	return (i - 1);
}

int	tk_redir_out(t_msh **msh, const char *line, char *redir_out, int i)
{
	int			j;
	t_tk_lst	*new_tk;
	bool		flag;

	j = 0;
	flag = false;
	if (line[i + 1] == '|')
		flag = true;
	while (line[i] && line[i] == '>')
	{
		redir_out[j++] = line[i];
		i++;
	}
	if (flag)
		i++;
	redir_out[j] = '\0';
	if (redir_out[0] != '\0')
	{
		new_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk(*msh, new_tk, redir_out, REDIR_OUT);
	}
	return (i - 1);
}
