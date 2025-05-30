/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39_rm_empties.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:18:59 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/23 19:32:25 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	rm_empties(t_tk_lst **token)
{
	t_tk_lst	**curr;
	bool		env;

	curr = token;
	env = false;
	first_and_pipe(&curr, NULL, NULL);
	if (!(*curr)->prev)
		return ;
	if ((*curr)->type == ENV_CMD)
		env = true;
	while (*curr)
	{
		if (ft_strcmp("\'\'", (*curr)->content) == 0 && (*curr)->prev
			&& (*curr)->prev->content[0] == '$')
		{
			empties_rmv_exp(&curr);
			return ;
		}
		if (ft_strcmp("\'\'", (*curr)->content) == 0)
			rm_empties_case(curr, env);
		if (!(*curr)->prev)
			break ;
		*curr = (*curr)->prev;
		first_and_pipe(NULL, *curr, &env);
	}
}

void	rm_empties_case(t_tk_lst **curr, bool env)
{
	if ((*curr)->next && (*curr)->next->type == W_SPACE
		&& (*curr)->next->next)
	{
		if (((*curr)->next->next->type == BT_CMD
				|| (*curr)->next->next->type == ARG) && !env)
			empties_rmv_tk(&curr);
	}
	else if ((*curr)->next && ((*curr)->next->type == BT_CMD
			|| (*curr)->next->type == ARG) && !env)
		empties_rmv_tk(&curr);
}

void	empties_rmv_exp(t_tk_lst ***curr)
{
	if ((**curr)->next)
	{
		(**curr)->next->quotes.sp_case = (**curr)->quotes.sp_case;
		(**curr)->prev->next = (**curr)->next;
		(**curr)->next->prev = (**curr)->prev;
	}
	else
	{
		(**curr)->prev->next = NULL;
		(**curr) = (**curr)->prev;
	}
}

void	empties_rmv_tk(t_tk_lst ***curr)
{
	(**curr)->next->quotes.sp_case = (**curr)->quotes.sp_case;
	if ((**curr)->prev)
	{
		if ((**curr)->prev->type == W_SPACE && (**curr)->prev->prev)
		{
			(**curr)->next->prev = (**curr)->prev->prev;
			(**curr)->prev->prev->next = (**curr)->next;
			(**curr) = (**curr)->prev->prev;
		}
		else
		{
			(**curr)->next->prev = (**curr)->prev;
			(**curr)->prev->next = (**curr)->next;
			(**curr) = (**curr)->prev;
		}
	}
	else
	{
		(**curr)->next->prev = NULL;
		(**curr) = (**curr)->next;
	}
}

void	first_and_pipe(t_tk_lst ***curr_f, t_tk_lst *curr_p, bool *env)
{
	if (curr_f && (**curr_f))
	{
		while ((**curr_f)->next)
			(**curr_f) = (**curr_f)->next;
	}
	if (curr_p)
	{
		if ((curr_p && curr_p->type == PIPE
				&& ((curr_p->prev && curr_p->prev->type != ENV_CMD)
					|| ((curr_p->prev && curr_p->prev->type == W_SPACE)
						&& (curr_p->prev->prev
							&& curr_p->prev->prev->type != ENV_CMD)))))
			*env = true;
	}
}
