/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:54 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	empty_case(t_msh **msh);

void	get_tokens(t_msh **msh, int i)
{
	const char		*line;
	t_quote			quotes;
	
	quotes.in_squotes = false;
	quotes.in_dquotes = false;
	quotes.quote_char = '\0';
	line = (*msh)->prompt_line;
	i = -1;
	while(line[++i])
	{
		quotes.space_case = false;
		sort_out_quotes(&i, line, &quotes);
		if ((!quotes.in_squotes || !quotes.in_dquotes) && ft_strchr(QUOTE, line [i]))
			i++;
		if (!ft_strchr(QUOTE, line[i]) && (extra_check(&(*msh), &i, line[i], &quotes)))
				;
		else if (ft_strchr(QUOTE, line[i]))
			i--;
		else
			break ;
	}
	sub_tokenize(&(*msh));
	if(!(*msh)->token_list)
		empty_case(msh);
	if ((*msh)->debug_mode)  //DEBUG TO DELETE
	{	
		print_tokens(&(*msh));
		ft_printf("------------------------------\n");
	}
	parse_line(&(*msh));
	// ft_printf("------------------------------\n");
	// if ((*msh)->debug_mode)
	// 	print_tokens(&(*msh)); //DEBUG TO DELETE
	// ft_printf("------------------------------\n");
	return ;
}

void	empty_case(t_msh **msh)
{
	t_tk_lst	*empty_tk;
	
	if (!(*msh)->token_list)
	{
		empty_tk = ft_calloc(1, sizeof(t_tk_lst));
		app_tk((*msh), empty_tk, "''", ARG);	
	}
	return ;
}

bool	extra_check(t_msh **msh, int *i, char c, t_quote *quotes)
{	
	if (ft_strchr(WHITESPACE, c) && !quotes->in_quotes)
		*i = tk_space(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && !quotes->in_quotes)
		*i = tk_word(msh, *i);
	else if (quotes->in_quotes) //deleted !ft_strchr(OPERATOR, c) && 
		*i = tk_word_qt(msh, *i, &quotes->in_quotes, &quotes->quote_char);
	else if (c == '|' && !quotes->in_quotes)
		*i = tk_pipe(msh, *i);
	else if (c == '>' && !quotes->in_quotes)
		*i = redir_r(msh, *i);
	else if (c == '<' && !quotes->in_quotes)
		*i = redir_l(msh, *i);
	else
		return (false);
	return (true);
}

void	sub_tokenize(t_msh **msh)
{
	t_tk_lst	*curr;
	char		*word;
	char		*env_path;

	handle_filename((*msh)->token_list);
	curr = (*msh)->token_list;
	word = NULL;
	env_path = get_path((*msh)->envp_list);
	while(curr)
	{
		if (curr->type == WORD)
		{
			word = curr->content;
			if (check_builtin(word))
				curr->type = BT_CMD;
			else if (check_env_cmd(word, env_path, -1))
				curr->type = ENV_CMD;
			else
				curr->type = ARG;
		}
		curr = curr->next;
	}
	check_rep_cmd(&(*msh));
	join_filename(&(*msh));
}
