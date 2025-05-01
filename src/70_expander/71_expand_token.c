/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_expand_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:48:17 by isabel            #+#    #+#             */
/*   Updated: 2025/05/01 15:15:36 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_tk(t_msh **msh, char **arg)
{
	char	*pre_c;
	char	**kw;
	char	*post_c;
	char	*new_arg;
	int 	i;

	ft_init_var((void **)&pre_c, (void **)&kw,
		(void **)&post_c, (void **)&new_arg);
	i = -1;
	pre_c = get_pre_cont(*arg, &i);
	kw = build_kw_array(*arg, &i);
	post_c = get_post_cont(*arg, &i);
	new_arg = build_new_arg(msh, kw);
	subst_arg(arg, pre_c, new_arg, post_c);
}

char	**build_kw_array(char *arg, int *i)
{
	char	**kw;
	int		count;
	int		k;
	int		tmp;
	
	kw = NULL;
	tmp = *i;
	count = count_exp(arg, tmp);
	k = 0;
	if (count)
		kw = ft_calloc((count + 1), sizeof(char *));
	while(arg[*i] && !ft_strchr(WHITESPACE, arg[*i])
		&& !ft_strchr(SYM_EXP, arg[*i]))
	{
		if (arg[*i] == '$' && !arg[*i + 1])
			kw[k] = kw_array_util(arg, &k, &i, 1);
		if (arg[*i] == '$' && arg[*i + 1])
			kw[k] = kw_array_util(arg, &k, &i, 2);
		if (arg[*i] && (ft_strchr(SYM_EXP, arg[*i]) || (arg[*i] != '$')))
			kw[++k] = kw_array_util(arg, &k, &i, 3);
		if (arg[*i])
			k++;
	}
	kw[++k] = NULL;
	return (kw);
}

int	count_exp(char *arg, int i)
{
	int	count;
	
	count = 0;
	while(arg[i] && !ft_strchr(WHITESPACE, arg[i]))
	{
		if (arg[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*kw_array_util(char *arg, int *k, int **i, int n)
{
	if (!n)
		return (NULL);
	if (n == 1)
	{
		(**i)++;
		return (ft_strdup("$"));
	}
	if (n == 2)
		return (get_key_word(arg, *i));
	else
	{
		(void)*k;
		return (get_mid_cont(arg, *i));
	}
}

char	*build_new_arg(t_msh **msh, char **kw)
{
	char	*new_arg;
	char	*new_c;
	int		count;
	int		k;
	bool	flag;
	
	ft_init_var((void **)&new_arg, (void **)&new_c, NULL, NULL);
	k = -1;
	flag = false;
	count = count_kw(kw, &flag);
	while(++k < count)
	{
		new_c = NULL;
		if ((expand_case(msh, &new_c, kw[k], &flag) == 1)
			|| (expand_case(msh, &new_c, kw[k], &flag) == 4))
			;
		else if (expand_case(msh, &new_c, kw[k], &flag) == 3 && !flag)
			new_c = get_env_cont((*msh)->envp_list, kw[k]);
		else if (expand_case(msh, &new_c, kw[k], &flag) == 3 && flag)
			new_c = ft_strdup(kw[k]);
		if(!new_c)
			new_c = NULL;
		new_arg = safe_strjoin(new_arg, new_c);
	}
	return (new_arg);
}

int	count_kw(char **kw, bool *flag)
{
	int	k;
	int	count;
	
	k = 0;
	count = 0;
	while(kw[k])
	{
		if (kw[k][0] == '$' && !kw[k][1])
			*flag = true;
		count++;
		k++;
	}
	return (count);
}

int	expand_case(t_msh **msh, char **new_cont, char *kw, bool *flag)
{
	if (!kw || ft_strchr(WHITESPACE, kw[0]) || !kw[0])
		return (1);
	if (ft_strcmp(kw, "0") == 0)
	{
		*new_cont = ft_strdup("minishell");
		return (2);
	}
	else if(ft_strcmp(kw, "?") == 0)
	{
		*new_cont = ft_strdup(ft_itoa(exit_value(msh, 0, 0, 0)));
		*flag = true;
		return (2);
	}
	else if(ft_strchr(SYM_EXP, kw[0]))
	{
		*new_cont = ft_strdup(kw);
		return (4);
	}
	return (3);
}

void	subst_arg(char **arg, char *pre_c, char *new_c, char *post_c)
{
	char	*final_content;
	
	if (new_c)
	{
		final_content = get_final_cont(new_c, pre_c, post_c);
		free(*arg);
		*arg = ft_strdup(final_content);
	}
	else if(pre_c || post_c)
	{	
		if (pre_c)
			final_content = ft_strdup(pre_c);
		if (post_c)
			final_content = ft_strjoin(final_content, ft_strdup(post_c));
		free(*arg);
		*arg = ft_strdup(final_content);
	}
	else
		*arg = NULL;
}

/*
char	*process_keywords(t_msh **msh, char **kw);
void	fill_kw_array(char *s, char **kw, int *k, bool *x, int *i);
int	count_dollars(char *s, int i);
char	**alloc_kw(int count);
char	**build_kw_array(char *s, char **post_c);
int		get_index_init(void);

void	expand_tk(t_msh **msh, char **arg)
{
	char	*pre_c;
	char	**kw;
	char	*post_c;
	char	*new_arg;
	char	*s;
	int 	i;

	i = get_index_init();
	pre_c = NULL;
	kw = NULL;
	post_c = NULL;
	new_arg = NULL;
	s = *arg;
	pre_c = get_pre_cont(*arg, &i);

	kw = build_kw_array(s, &post_c);
	new_arg = process_keywords(msh, kw);
	subst_arg(arg, pre_c, new_arg, post_c);
}

char	**build_kw_array(char *s, char **post_c)
{
	int		i;
	int		k;
	bool	x;
	char	**kw;
	int		tmp;

	i = get_index_init();
	k = 0;
	x = false;
	tmp = i;
	i = tmp;
	kw = alloc_kw(count_dollars(s, i));
	i = tmp;
	fill_kw_array(s, kw, &k, &x, &i);
	kw[k + 1] = NULL;
	*post_c = get_post_cont(s, &i);
	return (kw);
}

char	**alloc_kw(int count)
{
	char	**kw;
	int		total;

	kw = NULL;
	total = count + 11;
	if (count > 0)
		kw = ft_calloc(total, sizeof(char *));
	return (kw);
}

int	count_dollars(char *s, int i)
{
	int count;

	count = 0;
	while (s[i] && !ft_strchr(WHITESPACE, s[i]))
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	fill_kw_array(char *s, char **kw, int *k, bool *x, int *i)
{
	while (s[*i] && !ft_strchr(WHITESPACE, s[*i]) && !ft_strchr(SYM_EXP, s[*i]))
	{
		if (s[*i] == '$' && !s[*i + 1])
		{
			*x = true;
			(*i)++;
			kw[*k] = ft_strdup("$");
		}
		if (s[*i] == '$' && s[*i + 1])
			kw[*k] = get_key_word(s, i);
		if (s[*i] && ft_strchr(SYM_EXP, s[*i]))
		{
			(*k)++;
			kw[*k] = get_mid_cont(s, i);
		}
		if (s[*i] && s[*i] != '$')
		{
			(*k)++;
			kw[*k] = get_mid_cont(s, i);
		}
		if (s[*i])
			(*k)++;
	}
}

int	special_exp(t_msh **msh, char **new_cont, char *kw, bool *x)
{
	if (!kw || ft_strchr(WHITESPACE, kw[0]) || !kw[0])
		return (1);
	if (ft_strcmp(kw, "0") == 0)
	{
		*new_cont = ft_strdup("minishell");
		return (2);
	}
	else if(ft_strcmp(kw, "?") == 0)
	{
		*new_cont = ft_strdup(ft_itoa(exit_value(msh, 0, 0, 0)));
		*x = true;
		return (2);
	}
	else if(ft_strchr(SYM_EXP, kw[0]))
	{
		*new_cont = ft_strdup(kw);
		return (4);
	}
	return (3);
}

char	*process_keywords(t_msh **msh, char **kw)
{
	int		i;
	char	*new_arg;
	char	*new_c;
	bool	x;
	int		ret;

	i = 0;
	new_arg = NULL;
	new_c = NULL;
	x = false;
	while (kw[i])
	{
		ret = special_exp(msh, &new_c, kw[i], &x);
		if (ret == 3 && !x)
			new_c = get_env_cont((*msh)->envp_list, kw[i]);
		else if (ret == 3 && x)
			new_c = ft_strdup(kw[i]);
		if (!new_c)
			new_c = NULL;
		new_arg = safe_strjoin(new_arg, new_c);
		if (new_c)
			new_c = NULL;
		i++;
	}
	return (new_arg);
}

int	get_index_init(void)
{
	int	i;

	i = -1;
	return (i);
}


void	expand_tk(t_msh **msh, char **arg)
{
	char	*pre_c;
	char	**kw;
	char	*post_c;
	char	*new_c;
	int		i;
	int		k;
	int		tmp_i;
	int		count;
	char	*new_arg;
	char 	*s;
	bool	x;
	
	i = -1;
	k = 0;
	pre_c = get_pre_cont(*arg, &i);
	tmp_i = i;
	count = 0;
	s = *arg;
	x = false;
	
	//COUNT $
	while(s[i] && !ft_strchr(WHITESPACE, s[i]))
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	if (count)
		kw = ft_calloc((count + 1), sizeof(char *));

	//GET KW + MID CONTENT
	i = tmp_i;
	while(s[i] && !ft_strchr(WHITESPACE, s[i]) && !ft_strchr(SYM_EXP, s[i]))
	{
		if (s[i] == '$' && !s[i + 1])
		{
			x = true;
			i++;
			kw[k] = ft_strdup("$");
		}
		if (s[i] == '$' && s[i + 1])
			kw[k] = get_key_word(s, &i);
		if (s[i] && ft_strchr(SYM_EXP, s[i]))
		{
			k++;
			kw[k] = get_mid_cont(s, &i);
		}
		if (s[i] && (s[i] != '$'))
		{
			k++;
			kw[k] = get_mid_cont(s, &i);
		}
		if (s[i])
			k++;
	}
	kw[++k] = NULL;
	//GET POST CONTENT
	post_c = get_post_cont(*arg, &i);

	//BUILD FINAL
	i = 0;
	new_arg = NULL;
	while(i < k)
	{
		if (special_exp(msh, &new_c, kw[i], &x) == 1)
			;
		else if (special_exp(msh, &new_c, kw[i], &x) == 4)
			;
		else if (special_exp(msh, &new_c, kw[i], &x) == 3 && !x)
			new_c = get_env_cont((*msh)->envp_list, kw[i]);
		else if (special_exp(msh, &new_c, kw[i], &x) == 3 && x)
			new_c = ft_strdup(kw[i]);
		if(!new_c)
			new_c = NULL;
		new_arg = safe_strjoin(new_arg, new_c);
		if (new_c)
			new_c = NULL;
		i++;
	}
	//SUBS ARG
	subst_arg(arg, pre_c, new_arg, post_c);
//	ft_free_arrays((void **)kw);
}
*/
