/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_rm_empties.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:18:59 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/10 20:42:06 by isabel           ###   ########.fr       */
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
			&& (*curr)->prev->content[0] == '$' && !(tk_in_qts(*curr)))
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

void	empties_rmv_exp(t_tk_lst ***curr)
{
	t_tk_lst	*curr_prev;
	t_tk_lst	*curr_next;

	curr_prev = (**curr)->prev;
	if ((**curr)->next)
	{
		curr_next = (**curr)->next;
		(**curr)->next->quotes.sp_case = (**curr)->quotes.sp_case;
		free_tokens(**curr, 1);
		(**curr)->prev->next = curr_next;
		(**curr)->next->prev = curr_prev;
	}
	else
	{
		(**curr)->prev->next = NULL;
		free_tokens(**curr, 1);
		(**curr) = curr_prev;
	}
}

void	empties_rmv_tk(t_tk_lst ***curr)
{
	t_tk_lst	*curr_prev;

	if ((**curr)->prev && (**curr)->next)
	{
		(**curr)->next->quotes.sp_case = (**curr)->quotes.sp_case;
		if ((**curr)->prev->type == W_SPACE && (**curr)->prev->prev)
		{
			curr_prev = (**curr)->prev->prev;
			free_tokens((**curr)->prev, 1);
			(**curr)->next->prev = curr_prev;
			curr_prev->next = (**curr)->next;
			free_tokens(**curr, 1);
			(**curr) = curr_prev;
		}
		else
		{
			curr_prev = (**curr)->prev;
			(**curr)->next->prev = (**curr)->prev;
			(**curr)->prev->next = (**curr)->next;
			free_tokens(**curr, 1);
			(**curr) = curr_prev;
		}
	}
	else
		empties_rmv_tk_util(&curr);
}

void	empties_rmv_tk_util(t_tk_lst ****curr)
{
	t_tk_lst	*curr_prev;
	t_tk_lst	*curr_next;

	if ((***curr)->next)
		(***curr)->next->quotes.sp_case = (***curr)->quotes.sp_case;
	if ((***curr)->prev && !(***curr)->next)
	{
		(***curr)->prev->quotes.sp_case = (***curr)->quotes.sp_case;
		curr_prev = (***curr)->prev;
		(***curr)->prev->next = NULL;
		free_tokens(***curr, 1);
		(***curr) = curr_prev;
	}
	else
	{
		curr_next = (***curr)->next;
		(***curr)->next->prev = NULL;
		free_tokens(***curr, 1);
		(***curr) = curr_next;
	}
}

void	empties_rmv_doll(t_tk_lst ***tk)
{
	t_tk_lst	*curr;
	t_tk_lst	*prev;

	curr = (**tk)->next;
	prev = curr->prev;
	if (curr->next)
	{
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
		free_tokens(curr, 1);
	}
	else
	{
		curr->prev->next = NULL;
		free_tokens(curr, 1);
		curr = prev;
	}
}
