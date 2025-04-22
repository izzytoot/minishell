/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:21:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/22 17:45:42 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	check_quote(bool *in_quotes, char *quote_char, char c)
// {
// 	if (!(*in_quotes))
//     {
// 		*in_quotes = true;
// 		*quote_char = c;
// 	}
// 	else if (*in_quotes && c == *quote_char)
// 	{
// 		*in_quotes = false;
// 		*quote_char = '\0';
// 	}
// }

// bool	check_in_quotes(char c, bool *in_squotes, bool *in_dquotes)
// {
// 	static char	quote_char;
// 	bool		res;

// 	res = false;
// 	if ((!(*in_squotes) && !(*in_dquotes)) && ft_strchr(QUOTE, c))
// 	{
// 		if (c == '"')
// 		{
// 			*in_squotes = true;
// 			res = true;
// 		}
// 		else if (c == 39)
// 			*in_dquotes = true;
// 		quote_char = c;
// 	}
// 	else if ((*in_squotes || *in_dquotes) && c == quote_char)
// 	{
// 		if (in_squotes)
// 			*in_squotes = false;
// 		else if (in_dquotes)
// 			*in_dquotes = false;
// 		quote_char = '\0';
// 	}
// 	return (in_squotes);
// }

void	app_tk(t_msh *msh, t_tk_lst *new_tk, char *content, t_tk_type type)
{
	new_tk->type = type;
	new_tk->content = ft_strdup(content);
	if (!new_tk->content)
	{
        free(new_tk);
        return ;
    }
	new_tk->next = msh->token_list;
	new_tk->prev = NULL;
	if (msh->token_list)
		msh->token_list->prev = new_tk;
	msh->token_list = new_tk;
}

char *get_path(t_list *envp_list)
{
	while(envp_list)
	{
		if (!ft_strncmp(envp_list->content, "PATH=", 5))
			return(envp_list->content + 5);
		envp_list = envp_list->next;
	}
	return (NULL);
}

void check_rep_cmd(t_msh **msh)
{
	t_tk_lst 	*curr;
	bool		cmd_ch;
	
	curr = (*msh)->token_list;
	cmd_ch = false;
	while (curr && curr->next)
		curr = curr->next;
	while(curr)
	{
		if (type_is_cmd(&curr->type))
		{
			if (cmd_ch)
				curr->type = ARG;
			else
				cmd_ch = true;
		}
		curr = curr->prev;
		if (curr && curr->type == PIPE)
			cmd_ch = false;
	}
}
