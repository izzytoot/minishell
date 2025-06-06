/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   85_get_parts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:41:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/06 17:44:06 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_pre_cont(char *arg, int *i)
{
	char	*pre_content;
	int		len;

	len = 0;
	while (!ft_strchr("$", arg[*i]))
	{
		len++;
		++(*i);
	}
	if (!len)
		return (NULL);
	pre_content = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = -1;
	while (!ft_strchr("$", arg[++*i]))
	{
		pre_content[len] = arg[len];
		len++;
	}
	pre_content[len] = '\0';
	return (pre_content);
}

char	*get_key_word(char *arg, int *i)
{
	char	*key_word;
	int		len;
	int		tmp_i;
	bool	flag;

	tmp_i = *i;
	flag = false;
	len = get_kw_len(arg, &i, tmp_i, &flag);
	if (flag)
		return (ft_strdup("?"));
	if (!len)
		return (NULL);
	key_word = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = tmp_i;
	while (!ft_strchr(WS, arg[(*i)++]) && !ft_strchr(SYM_EXP, arg[*i])
		&& !ft_strchr(QT, arg[*i]))
	{
		if (arg[*i] == '$' || ft_strchr(WS, arg[(*i)]))
			break ;
		key_word[len] = arg[*i];
		len++;
	}
	key_word[len] = '\0';
	return (key_word);
}

char	*get_mid_cont(char *arg, int *i)
{
	char	*mid_content;
	int		len;
	int		tmp_i;

	len = 0;
	tmp_i = *i;
	while (arg[*i] != '$' && !ft_strchr(WS, arg[*i]))
	{
		len++;
		(*i)++;
	}
	if (!len)
		return (NULL);
	mid_content = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = tmp_i;
	while (!ft_strchr("$", arg[*i])
		&& !ft_strchr(WS, arg[*i]))
	{
		mid_content[len] = arg[*i];
		len++;
		(*i)++;
	}
	mid_content[len] = '\0';
	return (mid_content);
}

char	*get_mid_cont_w_sp(char *arg, int *i)
{
	char	*mid_content;
	int		len;
	int		tmp_i;

	len = 0;
	tmp_i = *i;
	while (arg[*i] && arg[*i] != '$')
	{
		len++;
		(*i)++;
	}
	if (!len)
		return (NULL);
	mid_content = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = tmp_i;
	while (!ft_strchr("$", arg[*i]))
	{
		mid_content[len] = arg[*i];
		len++;
		(*i)++;
	}
	mid_content[len] = '\0';
	return (mid_content);
}

char	*get_post_cont(char *arg, int *i)
{
	char	*post_content;
	int		len;
	int		tmp_i;

	len = 0;
	tmp_i = *i;
	if (!arg[*i])
		return (NULL);
	while (arg[(*i)])
	{
		len++;
		(*i)++;
	}
	if (len == 0)
		return (NULL);
	post_content = ft_calloc((len + 1), sizeof(char));
	len = 0;
	*i = tmp_i;
	while (arg[*i])
	{
		post_content[len++] = arg[*i];
		(*i)++;
	}
	post_content[len] = '\0';
	return (post_content);
}
