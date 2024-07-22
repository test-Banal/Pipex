/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:51:15 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/22 19:03:24 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1042
# endif

void	ft_error(void);
char	*ft_substr(char const *s, int start, int len);
int		count_words(char const *s, char c);
char	**main_split(char const *s, char c);
char	**ft_split(char const *s, char c);
char	**ft_split_b(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);

char	*ft_strchr_gnl(char const *string, int c);
char	*ft_strdup_gnl(char const *s);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif
