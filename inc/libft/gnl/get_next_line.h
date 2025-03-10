/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:30:53 by icunha-t          #+#    #+#             */
/*   Updated: 2024/11/28 16:08:30 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 1024

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buff;
	struct s_list	*next;
}				t_list;

int		ft_newline(t_list *list);
t_list	*find_last_node(t_list *list);
char	*ft_get_line(t_list *list);
void	ft_copy_str(t_list *list, char *str);
int		len_new_line(t_list *list);
void	ft_polish_list(t_list **list);
char	*get_next_line(int fd);
void	ft_dealloc(t_list **list, t_list *clean_node, char *buffer);
void	ft_new_list(t_list **list, int fd);
void	ft_put_buffer_in_list(t_list **list, char *buffer);

#endif
