/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_init_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:04:16 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/05 22:57:38 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_all_null(t_msh **msh)
{
	(*msh)->prompt_line = NULL;
	(*msh)->token_list = NULL;
	(*msh)->envp = NULL;
	(*msh)->envp_list = NULL;
	(*msh)->vars_list = NULL;
	(*msh)->export_only = NULL;
	(*msh)->tree_root = NULL;
	(*msh)->tmp_fname = NULL;
}
