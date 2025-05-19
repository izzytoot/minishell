/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   44_type_is_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:36:26 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/18 16:54:11 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	type_is_redir(t_tk_type *type)
{
	if (*type == REDIR_APP || *type == REDIR_HD || *type == REDIR_IN
		|| *type == REDIR_OUT)
		return (true);
	else
		return (false);
}

bool	type_is_word(t_tk_type *type)
{
	if (*type == WORD || *type == ARG || *type == BT_CMD || *type == ENV_CMD)
		return (true);
	else
		return (false);
}

bool	type_is_cmd(t_tk_type *type)
{
	if (*type == BT_CMD || *type == ENV_CMD)
		return (true);
	else
		return (false);
}

bool	type_is_arg(t_tk_type *type)
{
	if (*type == ARG)
		return (true);
	else
		return (false);
}
