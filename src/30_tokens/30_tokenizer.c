/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/22 18:43:01 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	get_tokens(t_msh **msh, int i)
// {
// 	const char		*line;
// 	t_quote_state	quote;
	
// 	quote.in_quotes = false;
// 	quote.quote_char = '\0';
// 	line = (*msh)->prompt_line;
// 	while(line[++i])
// 	{
// 		if (!quote.in_quotes && ft_strchr(QUOTE, line[i]))
// 		{
// 			check_in_quotes(line[i], &quote.in_quotes);
// 			if (quote.in_quotes)
// 				quote.quote_char = line[i];
// 		}
// 		else
// 			check_in_quotes(line[i], &quote.in_quotes);
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

void	get_tokens(t_msh **msh, int i)
{
	const char		*line;
	t_quote_state	quote;
	
	quote.in_squotes = false;
	quote.in_dquotes = false;
	quote.quote_char = '\0';
	line = (*msh)->prompt_line;
	while(line[++i])
	{
		if ((!quote.in_squotes && !quote.in_dquotes) && ft_strchr(QUOTE, line[i]))
		{
			check_squote(&quote.in_squotes, line[i]);
			check_dquote(&quote.in_dquotes, line[i]);
			if (quote.in_squotes || quote.in_dquotes)
				quote.quote_char = line[i];
		}
		else
		{
			check_squote(&quote.in_squotes, line[i]);
			check_dquote(&quote.in_dquotes, line[i]);
		}
		if (quote.in_squotes || quote.in_dquotes)
			quote.in_quotes = true;
		else
			quote.in_quotes = false;
		if ((!quote.in_squotes || !quote.in_dquotes) && ft_strchr(QUOTE, line[i]))
			i++;
		ft_printf("single quote is %d\n", quote.in_squotes);
		ft_printf("double quote is %d\n", quote.in_dquotes);
		ft_printf("quotes is %d\n", quote.in_quotes);
		if (!ft_strchr(QUOTE, line[i]))
		{
			if (extra_check(&(*msh), &i, line[i], quote))
				;
		}
		else if (ft_strchr(QUOTE, line[i]))
			i--;
		else
			break ;
	}
	sub_tokenize(&(*msh));
	if ((*msh)->debug_mode)
	{	
		print_tokens(&(*msh)); //DEBUG TO DELETE
		ft_printf("------------------------------\n");
	}
	parse_line(&(*msh));
	// ft_printf("------------------------------\n");
	// if ((*msh)->debug_mode)
	// 	print_tokens(&(*msh)); //DEBUG TO DELETE
	// ft_printf("------------------------------\n");
	return ;
} //FIQUEI AQUI

bool	extra_check(t_msh **msh, int *i, char c, t_quote_state quote)
{
	bool 		tmp_in_quotes;
	char 		tmp_qt_char;
	
	if (ft_strchr(WHITESPACE, c) && !quote.in_quotes)
		*i = token_is_space(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && !quote.in_quotes)
		*i = token_is_word(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && quote.in_quotes)
	{
		tmp_in_quotes = quote.in_quotes;
		tmp_qt_char = quote.quote_char;
		*i = token_is_word_in_quotes(msh, *i, &tmp_in_quotes, &tmp_qt_char);
	}
	else if (c == '|' && !quote.in_quotes)
		*i = token_is_pipe(msh, *i);
	else if (c == '>' && !quote.in_quotes)
		*i = redir_r(msh, *i);
	else if (c == '<' && !quote.in_quotes)
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
			if (!ft_strcmp(word, "echo") || !ft_strcmp(word, "cd") || !ft_strcmp(word, "pwd") || !ft_strcmp(word, "export") || 
				!ft_strcmp(word, "unset") || !ft_strcmp(word, "env") || !ft_strcmp(word, "exit"))
				curr->type = BT_CMD;
			else if (check_env_cmd(word, env_path, -1))
				curr->type = ENV_CMD;
			else
				curr->type = ARG;
		}
		curr = curr->next;
	}
	check_rep_cmd(&(*msh));
}

void	handle_filename(t_tk_lst *token_list)
{
	t_tk_lst *curr;

	curr = token_list;
	while (curr)
	{
		if (curr->type == REDIR_HD || curr->type == REDIR_APP || curr->type == REDIR_IN || curr->type == REDIR_OUT)
		{
			if (curr->prev->type == W_SPACE && curr->prev->prev->type == WORD)
				curr->prev->prev->type = FILE_NAME;
			else if (curr->prev->type == WORD)
				curr->prev->type = FILE_NAME;
		}
		curr = curr->next;
	}
}

char	*check_env_cmd(char *cmd, char *env_path, int i)
{
	char	**paths;
	char	*part_path;
	char	*cmd_path;
	
	paths = ft_split(env_path, ':');
	ft_init_var((void **)&part_path, (void **)&cmd_path, NULL, NULL);
	if (!paths)
		return (0);
	while(paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_arrays((void **)paths);
			return(cmd_path);
		}
		free(cmd_path);
	}
	ft_free_arrays((void **)paths);
	return(NULL);	
}
