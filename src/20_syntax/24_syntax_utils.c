/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:17:48 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 14:10:29 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	line_and_hd_index(t_msh **msh, const char **line, int *hd_index)
{
	char	*tmp_line;
	int		i;

	i = -1;
	*line = (*msh)->prompt_line;
	if (!*line[0])
		return (false);
	tmp_line = ft_strdup(*line);
	while (tmp_line[++i])
	{
		if (!ft_strchr(WS, tmp_line[i]))
			break ;
	}
	if (tmp_line[i] == '\0')
	{
		tmp_line = safe_free(tmp_line);
		return (false);
	}
	tmp_line = safe_free(tmp_line);
	*hd_index = check_if_hd(*line);
	return (true);
}

bool	look_for_pipe(const char *line, int i)
{
	if (i == 0)
		return (false);
	if (line[i] == '>' && line[i - 1] != '>' && line[i + 1] == '|')
		return (false);
	i++;
	if (!line[i])
		return (false);
	while (line[i] && (ft_strchr(WS, line[i])))
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}
	return (false);
}

bool	check_in_quotes(char c, bool *in_quotes)
{
	static char	quote_char;

	if (!(*in_quotes) && ft_strchr(QT, c))
	{
		*in_quotes = true;
		quote_char = c;
	}
	else if (*in_quotes && c == quote_char)
	{
		*in_quotes = false;
		quote_char = '\0';
	}
	return (in_quotes);
}

int	check_if_hd(const char *line)
{
	int		i;
	bool	in_quotes;
	int		hd_start;

	i = -1;
	in_quotes = false;
	hd_start = -1;
	while (line[++i])
	{
		check_in_quotes(line[i], &in_quotes);
		if (line[i] && !in_quotes && (line[i] == '<' && line[i + 1] == '<'))
		{
			hd_start = i;
			i = i + 2;
			while (line[i] && ft_strchr(WS, line[i]))
				i++;
			if (line[i] == '-')
				i++;
			if (!line[i] && ft_strchr(NON_EOF, line[i]))
				return (-1);
			return (hd_start);
		}
	}
	return (-1);
}

char	*get_eof(const char *line, int hd_index)
{
	char	*eof;
	int		i;
	int		size;
	int		eof_s;

	hd_index += 2;
	i = 0;
	size = 0;
	while (line[hd_index] && ft_strchr(WS, line[hd_index]))
		hd_index++;
	if (!ft_strchr(WS, line[hd_index - 1])
		&& ((line[hd_index] == '-' || line[hd_index] == '!')))
		hd_index++;
	eof_s = hd_index;
	while (!ft_strchr(WS, line[++hd_index]))
		size++;
	eof = ft_calloc((size + 1), sizeof(char));
	while (!ft_strchr(WS, line[eof_s]))
	{
		eof[i] = line[eof_s];
		eof_s++;
		i++;
	}
	eof[i] = '\0';
	return (eof);
}
