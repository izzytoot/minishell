/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:16 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/08 17:18:16 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_all_null (t_minishell **msh)
{
	// (*msh)->dir = NULL;
	// (*msh)->msh_pid = 0;
	(*msh)->prompt_line = NULL;
	(*msh)->token_list = NULL;
	(*msh)->envp = NULL;
	(*msh)->envp_list = NULL;
	(*msh)->tree_root = NULL;
}

