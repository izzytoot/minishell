/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39_rm_empties.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:18:59 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/30 15:25:21 by isabel           ###   ########.fr       */
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
	else if (!(*curr)->next && (*curr)->prev && !(*curr)->quotes.sp_case
			&& ((*curr)->prev->type == BT_CMD || (*curr)->prev->type == ARG) && !env)
			empties_rmv_tk(&curr);
}

void	empties_rmv_exp(t_tk_lst ***curr)
{
	t_tk_lst *curr_prev;
	t_tk_lst *curr_next;
	
	curr_prev = (**curr)->prev;
	if ((**curr)->next)
	{
		curr_next = (**curr)->next;
		(**curr)->next->quotes.sp_case = (**curr)->quotes.sp_case;
		free_tokens(**curr, 1); //leaks - added free curr
		(**curr)->prev->next = curr_next;
		(**curr)->next->prev = curr_prev;
	}
	else
	{
		(**curr)->prev->next = NULL;
		free_tokens(**curr, 1); //leaks - added free curr
		(**curr) = curr_prev;
	}
}
void	empties_rmv_tk_util(t_tk_lst ****curr);

void	empties_rmv_tk(t_tk_lst ***curr)
{
	t_tk_lst *curr_prev;

	if ((**curr)->prev && (**curr)->next)
	{
		(**curr)->next->quotes.sp_case = (**curr)->quotes.sp_case;
		if ((**curr)->prev->type == W_SPACE && (**curr)->prev->prev)
		{
			curr_prev = (**curr)->prev->prev; // add for curr->prev - free_tokens(**curr, 1); //leaks - added free curr
			free_tokens((**curr)->prev, 1);
			(**curr)->next->prev = (**curr)->prev->prev;
			(**curr)->prev->prev->next = (**curr)->next;
			free_tokens(**curr, 1); //leaks - added free curr
			(**curr) = curr_prev;
		}
		else
		{
			curr_prev = (**curr)->prev;
			(**curr)->next->prev = (**curr)->prev;
			(**curr)->prev->next = (**curr)->next;
			free_tokens(**curr, 1); //leaks - added free curr
			(**curr) = curr_prev;
		}
	}
	else
		empties_rmv_tk_util(&curr);
}

void	empties_rmv_tk_util(t_tk_lst ****curr)
{
	t_tk_lst *curr_prev;
	t_tk_lst *curr_next;

	if ((***curr)->next)
		(***curr)->next->quotes.sp_case = (***curr)->quotes.sp_case;
	if ((***curr)->prev && !(***curr)->next)
	{
		(***curr)->prev->quotes.sp_case = (***curr)->quotes.sp_case;
		curr_prev = (***curr)->prev;
		(***curr)->prev->next = NULL;
		free_tokens(***curr, 1); //leaks - added free curr
		(***curr) = curr_prev;
	}
	else
	{
		curr_next = (***curr)->next;
		(***curr)->next->prev = NULL;
		free_tokens(***curr, 1); //leaks - added free curr
		(***curr) = curr_next;
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
