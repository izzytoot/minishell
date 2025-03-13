/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/13 17:13:56 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_tokens(t_minishell	**msh)
{
	int		i;
	int 	j;
	char	buffer[100];
	t_token_lst	*new_token;
	
	i = -1;
	while((*msh)->promt_line[++i])
	{
		ft_printf("1\n");
		j = -1;
		while((*msh)->promt_line[i] != '|' && (*msh)->promt_line[i] != '<' && (*msh)->promt_line[i] != '>')
		{
			buffer[++j] = (*msh)->promt_line[i];
			i++;
		}
		ft_printf("2\n");
		new_token = calloc(1, sizeof(t_token_lst));
		add_token(&(*msh), new_token, buffer, CMD);
		ft_bzero(buffer, 100);
		i++;
		buffer[++j] = (*msh)->promt_line[i];
		if((*msh)->promt_line[i] == '|')
		{
			new_token = calloc(1, sizeof(t_token_lst));
			add_token(&(*msh), new_token, buffer, PIPE);
		}
		else if ((*msh)->promt_line[i] == '>')
		{
			new_token = calloc(1, sizeof(t_token_lst));
			add_token(&(*msh), new_token, buffer, REDIR_R_1);
		}	
		else if ((*msh)->promt_line[i] == '<')
		{
			new_token = calloc(1, sizeof(t_token_lst));
			if ((*msh)->promt_line[i + 1] == '<')
				add_token(&(*msh), new_token, buffer, REDIR_L_2);
			else
				add_token(&(*msh), new_token, buffer, REDIR_L_1);
		}
	}
}

void	add_token(t_minishell **msh, t_token_lst *new_token, char *content, t_token_type type)
{
	int	i;
	
	i = -1;
	ft_printf("3\n");
	new_token->next = (*msh)->token_list;
	printf("%s\n", new_token->next->content);
	new_token->prev = find_last_token((*msh)->token_list);
	ft_printf("4\n");
	(*msh)->token_list = new_token;
	(*msh)->token_list->type = type;
	(*msh)->token_list->content = calloc(ft_strlen(content) + 1, sizeof(char));
	while(content[++i])
		(*msh)->token_list->content[i] = content[i];
	ft_printf("%s\n", (*msh)->token_list->content);
}

t_token_lst	*find_last_token(t_token_lst *token_list)
{
	while(token_list->next)
		token_list = token_list->next;
	return(token_list);
}