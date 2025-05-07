/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   71_expand_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:48:17 by isabel            #+#    #+#             */
/*   Updated: 2025/05/07 16:04:00 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_tk(t_msh **msh, char **arg, char **fname)
{
	char	*pre_c;
	char	**kw;
	char	*post_c;
	char	*new_arg;
	int 	i;

	ft_init_var((void **)&pre_c, (void **)&kw,
		(void **)&post_c, (void **)&new_arg);
	i = -1;
	if (arg)
	{
		pre_c = get_pre_cont(*arg, &i);
		kw = build_kw_array(*arg, &i);
		post_c = get_post_cont(*arg, &i);
		new_arg = build_new_arg(msh, kw);
		subst_arg(arg, pre_c, new_arg, post_c);
	}
	else if (fname)
	{
		pre_c = get_pre_cont(*fname, &i);
		kw = build_kw_array(*fname, &i);
		post_c = get_post_cont(*fname, &i);
		new_arg = build_new_arg(msh, kw);
		subst_fname(fname, pre_c, new_arg, post_c);
	}
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
		&& !ft_strchr(SYM_EXP, arg[*i]) && !ft_strchr(QUOTE, arg[*i]))
	{
		if (arg[*i] == '$' && !arg[*i + 1])
			kw[k] = kw_array_util(arg, &k, &i, 1);
		if (arg[*i] == '$' && arg[*i + 1])
			kw[k] = kw_array_util(arg, &k, &i, 2);
		if (arg[*i] && check_mid(arg[*i])) 
			kw[++k] = kw_array_util(arg, &k, &i, 3);
		if (arg[*i])
			k++;
	}
	kw[++k] = NULL;
	return (kw);
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
			new_c = get_env_cont((*msh)->envp_list, (*msh)->vars_list, kw[k]);
		else if (expand_case(msh, &new_c, kw[k], &flag) == 3 && flag)
			new_c = ft_strdup(kw[k]);
		if(!new_c)
			new_c = NULL;
		new_arg = safe_strjoin(new_arg, new_c);
	}
	return (new_arg);
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
