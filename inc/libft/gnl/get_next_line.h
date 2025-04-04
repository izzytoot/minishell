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

typedef struct s_gnllist
{
	char				*str_buff;
	struct s_gnllist	*next;
}				t_gnllist;

int			ft_newline(t_gnllist *list);
t_gnllist	*find_last_node(t_gnllist *list);
char		*ft_get_line(t_gnllist *list);
void		ft_copy_str(t_gnllist *list, char *str);
int			len_new_line(t_gnllist *list);
void		ft_polish_list(t_gnllist **list);
char		*get_next_line(int fd);
void		ft_dealloc(t_gnllist **list, t_gnllist *clean_node, char *buffer);
void		ft_new_list(t_gnllist **list, int fd);
void		ft_put_buffer_in_list(t_gnllist **list, char *buffer);

#endif
