/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/17 11:55:47 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_tokens(t_minishell	**msh)
{
	int			i;
	const	char *line;
	
	i = 0;
	line = (*msh)->promt_line;
	while((*msh)->promt_line[i])
	{
		if (line[i] && !ft_strchr(TOKENS, line[i]) && !ft_strchr(WHITESPACE, line[i]))
			i = token_is_word(msh, i);
		else if (line[i] == '|')
			i = token_is_pipe(msh, i);
		else if (line[i] == '>')
			i = token_is_redir_r(msh, i);
		else if (line[i] == '<')
			i = token_is_redir_l(msh, i);
		else if (ft_strchr(WHITESPACE, line[i]))
			i++;
		else
			return ;
	}
}

int	token_is_word(t_minishell **msh, int start)
{
	int		i;
	int		j;
	char	word[100];
	t_token_lst	*new_token;
	const char *line;
	
	i = start;
	j = 0;
	line = (*msh)->promt_line;
	while(line[i] && !ft_strchr(TOKENS, line[i]))
	{
		if (line [i] == '\\' && line[i + 1])
			word[j++] = line[++i];
		else
			word[j++] = line[i];
		i++;
	}
	word[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, word, WORD);
	return(i);
}

int	token_is_pipe(t_minishell **msh, int start)
{
	int			i;
	int			j;
	char		pipe[100];
	t_token_lst	*new_token;
	const char *line;
	
	i = start;
	j = 0;
	line = (*msh)->promt_line;
	while(line[i] && line[i]== '|')
	{
		pipe[j++] = line[i];
		i++;
	}
	pipe[j] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	append_token(*msh, new_token, pipe, PIPE);
	return(i);
}

int	token_is_redir_r(t_minishell **msh, int start)
{
	int			i;
	int			j;
	char		redir_out[100];
	char		redir_app[100];
	t_token_lst	*new_token;
	const char *line;
	
	i = start;
	j = 0;
	line = (*msh)->promt_line;
	if (line[i] && line[i + 1] == '>')
	{
		while(line[i] && line[i] == '>')
		{
			redir_app[j++] = line[i];
			i++;
		}
		redir_app[j] = '\0';
		new_token = calloc(1, sizeof(t_token_lst));
		append_token(*msh, new_token, redir_app, REDIR_APP);
	}
	else
	{
		while(line[i] && line[i] == '>')
		{
			redir_out[j++] = line[i];
			i++;
		}
		redir_out[j] = '\0';
		new_token = calloc(1, sizeof(t_token_lst));
		append_token(*msh, new_token, redir_out, REDIR_OUT);
	}
	return(i);
}

int	token_is_redir_l(t_minishell **msh, int start)
{
	int			i;
	int			j;
	char		redir_in[100];
	char		redir_hd[100];
	t_token_lst	*new_token;
	const char *line;
	
	i = start;
	j = 0;
	line = (*msh)->promt_line;
	if (line[i] && line[i + 1] == '<')
	{
		while(line[i] && line[i] == '<')
		{
			redir_hd[j++] = line[i];
			i++;
		}
		redir_hd[j] = '\0';
		new_token = calloc(1, sizeof(t_token_lst));
		append_token(*msh, new_token, redir_hd, REDIR_HD);
	}
	else
	{
		while(line[i] && line[i] == '<')
		{
			redir_in[j++] = line[i];
			i++;
		}
		redir_in[j] = '\0';
		new_token = calloc(1, sizeof(t_token_lst));
		append_token(*msh, new_token, redir_in, REDIR_IN);
	}
	return(i);
}

void	append_token(t_minishell *msh, t_token_lst *new_token, char *content, t_token_type type)
{
	t_token_lst *last;
	
	new_token->type = type;
	new_token->content = ft_strdup(content);
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!msh->token_list)
		msh->token_list = new_token;
	else
	{
		last = find_last_token(msh->token_list);
		last->next = new_token;
		new_token->prev = last;
	}
}

t_token_lst	*find_last_token(t_token_lst *token_list)
{
	t_token_lst	*current;
	
	current = token_list;
	while(current && current->next)
		current = current->next;
	return(current);
}
