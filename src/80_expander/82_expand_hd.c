/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   82_expand_hd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:43:50 by isabel            #+#    #+#             */
/*   Updated: 2025/06/04 00:53:34 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_line(t_msh **msh, t_hd_lines *lines,
	t_tree_nd *curr_nd, int hd_fd)
{
	int		i;
	char	*unsplit;

	i = 0;
	if (!curr_nd->exp_hd || !count_exp(lines->new_l, 0))
		ft_putstr_fd(lines->new_l, hd_fd);
	else
	{
		lines->exp_newl = ft_split(lines->new_l, ' ');
		while (lines->exp_newl[i])
		{
			if (count_exp(lines->exp_newl[i], 0))
			{
				lines->exp_newl[i] = expand_word(msh, lines->exp_newl[i]);
				lines->ch_exp = true;
			}
			i++;
		}
		unsplit = ft_unsplit(lines->exp_newl);
		ft_putstr_fd(unsplit, hd_fd);
		unsplit = safe_free(unsplit);
	}
}

char	*expand_word(t_msh **msh, char *word)
{
	t_exp_cont	parts;
	t_kw		*kw_lst;
	int			i;

	ft_init_var((void **)&parts.pre_c, (void **)&parts.new_c,
		(void **)&parts.post_c, NULL);
	i = 0;
	kw_lst = NULL;
	if (word)
	{
		parts.pre_c = get_pre_cont_hd(word, &i);
		build_kw_list(&kw_lst, word, &i);
		parts.post_c = get_post_cont(word, &i);
		expand_kw(msh, &kw_lst);
		parts.new_c = get_exp_cont(&kw_lst);
		subst_arg(&word, &parts);
		free_kw_structs(&parts, &kw_lst);
	}
	else
		return (NULL);
	return (word);
}

char	*get_pre_cont_hd(char *arg, int *i)
{
	char	*pre_content;
	int		len;

	len = len_pre_cont_hd(arg, 0);
	if (!len)
		return (NULL);
	*i = len;
	pre_content = ft_calloc((len + 1), sizeof(char));
	len = wr_pre_cont_hd(arg, &pre_content, 0, 0);
	pre_content[len] = '\0';
	return (pre_content);
}

int	len_pre_cont_hd(char *arg, int i)
{
	if (arg[i] == '$' && ft_strchr(QT, arg[i + 1]))
		i++;
	while (arg[i] && arg[i] != '$')
	{
		i++;
		if (arg[i] == '$' && ft_strchr(QT, arg[i + 1]))
			i = len_pre_cont_hd(arg, i);
	}
	return (i);
}

int	wr_pre_cont_hd(char *arg, char **pre_content, int i, int len)
{
	if (arg[i] == '$' && ft_strchr(QT, arg[i + 1]))
	{
		(*pre_content)[len] = arg[len];
		len++;
		i++;
	}
	while (arg[i] && arg[i] != '$')
	{
		(*pre_content)[len] = arg[len];
		len++;
		i++;
		if (arg[i] == '$' && ft_strchr(QT, arg[i + 1]))
			len = wr_pre_cont_hd(arg, pre_content, i, len);
	}
	return (len);
}
