/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:55:51 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/04/04 11:55:51 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_dprintf(int fd, const char *format, ...);
int		ft_dprint_args(va_list args, char letter, int fd);
int		ft_dprint_char(char c, int fd);
int		ft_dprint_str(char *str, int fd);
int		ft_dprint_int(int nbr, int fd);
int		ft_dprint_unsign(unsigned int i, int fd);
int		ft_dprint_ptr(unsigned long ptr, int fd);
int		ft_dprint_hex(unsigned int nbr, int lower, int fd);

#endif