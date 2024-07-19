/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:56:31 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/19 16:56:52 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	int		i;
	int		j;
	int		step;

	if (!s1 || !s2)
		return (NULL);
	step = 0;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	arr = (char *)malloc(i + j + 1);
	if (!arr)
		return (NULL);
	while (*s1)
		arr[step++] = *s1++;
	while (*s2)
		arr[step++] = *s2++;
	arr[step] = '\0';
	return (arr);
}
