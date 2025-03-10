/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:17:06 by icunha-t          #+#    #+#             */
/*   Updated: 2024/11/22 15:26:59 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(char const *str, char c)
{
	int		words;
	char	prev_char;
	int		i;

	words = 0;
	prev_char = c;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			prev_char = str[i];
		if (str[i] != c)
		{
			if (prev_char == c)
				words++;
		}
		prev_char = str[i];
		i++;
	}
	return (words);
}

static int	error_malloc(char **sing_word, int pos, int buffer)
{
	int	i;

	i = 0;
	sing_word[pos] = malloc(buffer);
	if (!sing_word[pos])
	{
		while (i < pos)
			free(sing_word[i++]);
		free(sing_word);
		return (1);
	}
	return (0);
}

static int	fill_new_arr(char **sing_word, char const *str, char c)
{
	int		i;
	int		len;

	i = 0;
	if (!sing_word)
		return (0);
	while (*str)
	{
		len = 0;
		while (*str == c && *str)
			++str;
		while (*str != c && *str)
		{
			++len;
			++str;
		}
		if (len)
		{
			if (error_malloc(sing_word, i, len + 1))
				return (1);
			ft_strlcpy(sing_word[i], str - len, len + 1);
		}
		++i;
	}
	return (0);
}

char	**ft_split(char const *str, char c)
{
	int		words;
	char	**new_arr;

	if (!str)
		return (NULL);
	words = count_words(str, c);
	new_arr = malloc((words + 1) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	new_arr[words] = NULL;
	if (fill_new_arr(new_arr, str, c))
		return (NULL);
	return (new_arr);
}
