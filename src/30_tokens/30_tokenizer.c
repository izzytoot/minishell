/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/23 12:50:32 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

bool	extra_check(t_msh **msh, int *i, char c, t_quote *quotes)
{	
	if (ft_strchr(WHITESPACE, c) && !quotes->in_quotes)
		*i = tk_space(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && !quotes->in_quotes)
		*i = tk_word(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && quotes->in_quotes)
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
}

void	handle_filename(t_tk_lst *token_list)
{
	t_tk_lst *curr;

	curr = token_list;
	while (curr)
	{
		if (curr->type == REDIR_HD || curr->type == REDIR_APP 
			|| curr->type == REDIR_IN || curr->type == REDIR_OUT)
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
