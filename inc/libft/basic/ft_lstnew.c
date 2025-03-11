/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:01:58 by icunha-t          #+#    #+#             */
/*   Updated: 2025/03/11 16:32:03 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_libftlist	*ft_lstnew(void *content)
{
	t_libftlist	*mynode;

	mynode = (t_libftlist *)malloc(sizeof(t_libftlist));
	if (!mynode)
		return (NULL);
	mynode->content = content;
	mynode->next = NULL;
	return (mynode);
}