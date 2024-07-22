/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:46:21 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/19 16:46:22 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1042
# endif

char    *ft_strchr_gnl(char const *string, int c);
char    *ft_strdup_gnl(char const *s);
char    *ft_strjoin_gnl(char const *s1, char const *s2);
int     ft_strlen_gnl(char const *c);
char    *get_next_line(int fd);


#endif
