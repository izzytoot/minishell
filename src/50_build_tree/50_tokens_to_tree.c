/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   50_tokens_to_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:07:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/12 16:53:14 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_line(t_msh **msh)
{
	t_tree_nd	*tree_root;

	tree_root = NULL;
	if (!(*msh)->token_list)
		return ;
	(*msh)->tree_root = build_pipe_nd(msh, &(*msh)->token_list);
	if ((*msh)->tree_root->type != PIPE)
		free_tokens((*msh)->token_list, 2);
	if ((*msh)->debug_mode)
		print_tree(tree_root);
}

t_tree_nd	*new_tree_nd(t_tk_lst *curr_tk, t_tk_type *type, char *content)
{
	t_tree_nd	*new_nd;

	new_nd = ft_calloc(1, sizeof(t_tree_nd));
	if (!new_nd)
		return (NULL);
	if (content)
		new_nd->op_content = ft_strdup(content);
	new_nd->cmd_content = NULL;
	if (type)
		new_nd->type = *type;
	else
		new_nd->type = -1;
	if (curr_tk)
		add_quote_structs(new_nd, curr_tk);
	new_tree_nd_util(new_nd);
	return (new_nd);
}

void	new_tree_nd_util(t_tree_nd	*new_nd)
{
	new_nd->args = NULL;
	new_nd->nb_arg = 0;
	new_nd->left = NULL;
	new_nd->right = NULL;
	new_nd->cmd = NULL;
	new_nd->fd = -1;
	new_nd->cmd_type = -1;
	new_nd->eof_ch = false;
	new_nd->tmp_file = NULL;
	new_nd->exp_hd = false;
	new_nd->cmd_r = false;
	new_nd->ch_ambg = false;
	new_nd->eof = NULL;
}

void	add_quote_structs(t_tree_nd *new_nd, t_tk_lst *token)
{
	t_tk_lst	*curr_tk;
	t_tk_lst	*curr_tk_tmp;
	int			count;

	curr_tk = token;
	curr_tk_tmp = token;
	count = 0;
	while (curr_tk)
	{
		if (curr_tk->type == ARG)
			count++;
		curr_tk = curr_tk->next;
	}
	if (count <= 0)
		return ;
	while (curr_tk_tmp)
	{
		if (curr_tk_tmp->type == ARG)
			app_qt(new_nd, curr_tk_tmp);
		curr_tk_tmp = curr_tk_tmp->next;
	}
}

void	app_qt(t_tree_nd *new_nd, t_tk_lst *token)
{
	t_quote	*new_quote;

	new_quote = ft_calloc(1, sizeof(t_quote));
	new_quote->content = ft_strdup(token->content);
	new_quote->in_dquotes = token->quotes.in_dquotes;
	new_quote->in_squotes = token->quotes.in_squotes;
	new_quote->sp_case = token->quotes.sp_case;
	new_quote->exp = token->quotes.exp;
	if (new_quote->in_dquotes || new_quote->in_squotes)
		new_quote->in_quotes = true;
	else
		new_quote->in_quotes = false;
	new_quote->quote_char = token->quotes.quote_char;
	new_quote->next = new_nd->quote_lst;
	new_quote->prev = NULL;
	if (new_nd->quote_lst)
		new_nd->quote_lst->prev = new_quote;
	new_nd->quote_lst = new_quote;
}
