/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:48:22 by npederen          #+#    #+#             */
/*   Updated: 2025/03/25 22:20:35 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft.h"

char	*ft_gnl_strjoin(char *s1, const char *s2);
char	*get_new_line(char *stash, char	*line);
char	*init_stash(int fd, char *stash, char *buffer);
char	*get_new_stash(char *stash);
char	*get_next_line(int fd);

#endif