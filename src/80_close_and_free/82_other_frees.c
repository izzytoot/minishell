/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   82_other_frees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:52:51 by isabel            #+#    #+#             */
/*   Updated: 2025/05/07 19:57:34 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**free_kw_error(char **kw)
{
	ft_dprintf(STDERR_FILENO, ERR_KW);
	ft_free_arrays((void **)kw);
	return (NULL);
}