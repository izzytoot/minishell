/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:14:31 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/01 16:43:47 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_unsplit(char **args)
{
    char *result;
    char *temp;
    int i;

    if (!args || !args[0])
        return (NULL);
    result = ft_strdup(args[0]);
    i = 1;
    while (args[i])
    {
        temp = result;
        result = ft_strjoin(result, " ");
        free(temp);
        temp = result;
        result = ft_strjoin(result, args[i]);
        free(temp);
        i++;
    }
    return (result);
}
