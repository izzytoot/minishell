/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:01:58 by icunha-t          #+#    #+#             */
/*   Updated: 2025/05/27 10:48:46 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*mynode;

	mynode = (t_list *)malloc(sizeof(t_list));
	if (!mynode)
		return (NULL);
	mynode->content = content;
	mynode->next = NULL;
	return (mynode);
}
