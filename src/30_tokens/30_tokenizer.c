/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:33:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/17 16:11:26 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_tokens(t_minishell **msh, int i, char quote_char)
{
	const char *line;
	bool		in_quotes;

	line = (*msh)->prompt_line;
	in_quotes = false;
	while(line[++i])
	{
		if (!in_quotes && ft_strchr(QUOTE, line[i]))
		{
			check_in_quotes(line[i], &in_quotes);
			if (in_quotes)
				quote_char = line[i];
		}
		else
		 check_in_quotes(line[i], &in_quotes);
		if (!in_quotes && ft_strchr(QUOTE, line[i]))
			i++;
		if (any_of_these_tk(&(*msh), &i, line[i], in_quotes, quote_char))
		;
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
}

bool	any_of_these_tk(t_minishell **msh, int *i, char c, bool in_quotes, char quote_char)
{
	bool	tmp_in_quotes;
	char	tmp_qt_char;
	
	tmp_in_quotes = in_quotes;
	tmp_qt_char = quote_char;
	if (ft_strchr(WHITESPACE, c) && !tmp_in_quotes)
		*i = token_is_space(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && !tmp_in_quotes)
		*i = token_is_word(msh, *i);
	else if (!ft_strchr(OPERATOR, c) && tmp_in_quotes)	
		*i = token_is_word_in_quotes(msh, *i, &tmp_in_quotes, &tmp_qt_char);
	else if (c == '|' && !tmp_in_quotes)
		*i = token_is_pipe(msh, *i);
	else if (c == '>' && !tmp_in_quotes)
		*i = redir_r(msh, *i);
	else if (c == '<' && !tmp_in_quotes)
		*i = redir_l(msh, *i);
	else
		return (false);
	return (true);
}

void	sub_tokenize(t_minishell **msh)
{
	t_token_lst *current;
	char		*word;
	char	*env_path;

	handle_filename((*msh)->token_list);
	current = (*msh)->token_list;
	word = NULL;
	env_path = get_path((*msh)->envp_list);
	while(current)
	{
		if (current->type == WORD)
		{
			word = current->content;
			if (!ft_strcmp(word, "echo") || !ft_strcmp(word, "cd") || !ft_strcmp(word, "pwd") || !ft_strcmp(word, "export") || 
				!ft_strcmp(word, "unset") || !ft_strcmp(word, "env") || !ft_strcmp(word, "exit"))
				current->type = BT_CMD;
			else if (check_env_cmd(word, env_path, -1))
				current->type = ENV_CMD;
			else
				current->type = ARG;
		}
		current = current->next;
	}
	check_double_cmd(&(*msh));
}

void	handle_filename(t_token_lst *token_list)
{
	t_token_lst *current;

	current = token_list;
	while (current)
	{
		if (current->type == REDIR_HD || current->type == REDIR_APP || current->type == REDIR_IN || current->type == REDIR_OUT)
		{
			if (current->prev->type == W_SPACE && current->prev->prev->type == WORD)
				current->prev->prev->type = FILE_NAME;
			else if (current->prev->type == WORD)
				current->prev->type = FILE_NAME;
		}
		current = current->next;
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
