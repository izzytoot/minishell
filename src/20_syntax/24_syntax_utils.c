/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:17:48 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/22 17:47:18 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	look_for_pipe(const char *line, int i)
{
	i++;
	if (!line[i])
		return (false);
	while (line[i] && (ft_strchr(WHITESPACE, line[i])
			|| ft_strchr(QUOTE, line[i])))
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd(ERR_SYN_PIPE, STDERR_FILENO);
		return (true);
	}
	return (false);
}


// void	get_tokens(t_msh **msh, int i)
// {
// 	const char		*line;
// 	t_quote_state	quote;
	
// 	quote.in_squotes = false;
// 	quote.in_dquotes = false;
// 	quote.quote_char = '\0';
// 	line = (*msh)->prompt_line;
// 	while(line[++i])
// 	{
// 		if ((!quote.in_squotes && !quote.in_dquotes) && ft_strchr(QUOTE, line[i]))
// 		{
// 			check_in_quotes(line[i], &quote.in_squotes, &quote.in_dquotes);
// 			if (quote.in_squotes || quote.in_dquotes)
// 				quote.quote_char = line[i];
// 		}
// 		else
// 			check_in_quotes(line[i], &quote.in_squotes, &quote.in_dquotes);
// 		if (!quote.in_quotes && ft_strchr(QUOTE, line[i]))
// 			i++;
// 		if (extra_check(&(*msh), &i, line[i], quote))
// 		;
// 		else
// 			break ;
// 	}
// 	sub_tokenize(&(*msh));
// 	if ((*msh)->debug_mode)
// 	{	
// 		print_tokens(&(*msh)); //DEBUG TO DELETE
// 		ft_printf("------------------------------\n");
// 	}
// 	parse_line(&(*msh));
// 	// ft_printf("------------------------------\n");
// 	// if ((*msh)->debug_mode)
// 	// 	print_tokens(&(*msh)); //DEBUG TO DELETE
// 	// ft_printf("------------------------------\n");
// 	return ;
// }
bool	check_in_quotes(char c, bool *in_quotes)
{
	static char	quote_char;

	if (!(*in_quotes) && ft_strchr(QUOTE, c))
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
			while (line[i] && ft_strchr(WHITESPACE, line[i]))
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
	while (line[hd_index] && ft_strchr(WHITESPACE, line[hd_index]))
		hd_index++;
	if (!ft_strchr(WHITESPACE, line[hd_index - 1])
		&& ((line[hd_index] == '-' || line[hd_index] == '!')))
		hd_index++;
	eof_s = hd_index;
	while (!ft_strchr(WHITESPACE, line[++hd_index]))
		size++;
	eof = malloc(sizeof(char) * (size + 1));
	while (!ft_strchr(WHITESPACE, line[eof_s]))
	{
		eof[i] = line[eof_s];
		eof_s++;
		i++;
	}
	eof[i] = '\0';
	return (eof);
}
