/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:52:25 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/20 16:01:14 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	*ft_strcpy(char *dest, const char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_strdup(const char *s)
// {
// 	int		length;
// 	char	*new_str;

// 	length = ft_strlen(s);
// 	new_str = malloc((length + 1) * sizeof(char));
// 	if (!new_str)
// 		return (0);
// 	ft_strcpy(new_str, s);
// 	return (new_str);
// }

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*arr;
	int		i;
	int		j;

	str = (char *)s1;
	j = ft_strlen(str);
	arr = (char *)malloc(j + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < j)
	{
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
