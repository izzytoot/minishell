/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/14 17:53:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_tokens(t_minishell	**msh)
{
	int			i;

	i = -1;
	while((*msh)->promt_line[++i])
	{
		if ((*msh)->promt_line[i] != '|' && (*msh)->promt_line[i] != '<' && (*msh)->promt_line[i] != '>')
			i = token_is_cmd(msh, i);
		else if ((*msh)->promt_line[i] == '|')
			i = token_is_pipe(msh, i);
		else if ((*msh)->promt_line[i] == '>')
			i = token_is_redir_r(msh, i);
		else if ((*msh)->promt_line[i] == '<')
			i = token_is_redir_l(msh, i);
		else
			return ;
	}
}

int	token_is_cmd(t_minishell **msh, int start)
{
	int	i;
	int	j;
	char	cmd[100];
	t_token_lst	*new_token;
	
	i = start;
	j = -1;
	while((*msh)->promt_line[i] && (*msh)->promt_line[i] != '|' && (*msh)->promt_line[i] != '<' && (*msh)->promt_line[i] != '>')
	{
		cmd[++j] = (*msh)->promt_line[i];
		i++;
	}
	cmd[j++] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	add_token(*msh, new_token, cmd, CMD);
	return(i++);
}

int	token_is_pipe(t_minishell **msh, int start)
{
	int			i;
	int			j;
	char		pipe[100];
	t_token_lst	*new_token;
	
	i = start;
	j = -1;
	while((*msh)->promt_line[i] && (*msh)->promt_line[i] == '|')
	{
		pipe[++j] = (*msh)->promt_line[i];
		i++;
	}
	pipe[j++] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	add_token(*msh, new_token, pipe, PIPE);
	return(i++);
}

int	token_is_redir_r(t_minishell **msh, int start)
{
	int			i;
	int			j;
	char		redir_r[100];
	t_token_lst	*new_token;
	
	i = start;
	j = -1;
	while((*msh)->promt_line[i] && (*msh)->promt_line[i] == '>')
	{
		redir_r[++j] = (*msh)->promt_line[i];
		i++;
	}
	redir_r[j++] = '\0';
	new_token = calloc(1, sizeof(t_token_lst));
	add_token(*msh, new_token, redir_r, REDIR_R_1);
	return(i++);
}

int	token_is_redir_l(t_minishell **msh, int start)
{
	int			i;
	int			j;
	char		redir_l_1[100];
	char		redir_l_2[100];
	t_token_lst	*new_token;
	
	i = start;
	j = -1;
	if ((*msh)->promt_line[i + 1] == '<')
	{
		while((*msh)->promt_line[i] && (*msh)->promt_line[i] == '<')
		{
			redir_l_2[++j] = (*msh)->promt_line[i];
			i++;
		}
		redir_l_2[j++] = '\0';
		new_token = calloc(1, sizeof(t_token_lst));
		add_token(*msh, new_token, redir_l_2, REDIR_L_2);
	}
	else
	{
		while((*msh)->promt_line[i] && (*msh)->promt_line[i] == '<')
		{
			redir_l_1[++j] = (*msh)->promt_line[i];
			i++;
		}
		redir_l_1[j++] = '\0';
		new_token = calloc(1, sizeof(t_token_lst));
		add_token(*msh, new_token, redir_l_1, REDIR_L_1);
	}
	return(i++);
}

void	add_token(t_minishell *msh, t_token_lst *new_token, char *content, t_token_type type)
{
	int	i;
	
	i = -1;
	new_token->next = msh->token_list;
	new_token->prev = find_last_token(msh->token_list);
	msh->token_list = new_token;
	msh->token_list->type = type;
	msh->token_list->content = calloc(ft_strlen(content) + 1, sizeof(char));
	while(content[++i])
		msh->token_list->content[i] = content[i];
	ft_printf("token is %s\n", msh->token_list->content);
}

t_token_lst	*find_last_token(t_token_lst *token_list)
{
	t_token_lst	*current;
	
	current = token_list;
	while(current && current->next)
		current = current->next;
	return(current);
}
