/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:46:30 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/22 18:17:59 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc_check(char *argv)
{
	if (ft_strncmp(argv, "here_doc", 8) == 0
		&& ft_strlen(argv) == 8)
		return (1);
	return (0);
}

void	close_with_check(int fd)
{
	if (fd == -1)
	{
		perror("Failed close");
		exit(0);
	}
	close(fd);
}

void	here_doc(t_variables *variables, char *lim)
{
	char	*str;

	variables -> here_doc = open("here_doc", O_RDWR | O_CREAT, 0644);
	while (1)
	{
		write(1, "pipe heredoc> ", 15);
		str = get_next_line(0);
		if (!str || !*str)
		{
			free(str);
			write(1, "\n", 1);
			break ;
		}
		if (ft_strncmp(str, lim, ft_strlen(str) - 1) == 0
			&& ft_strncmp(str, lim, ft_strlen(lim)) == 0)
		{
			free(str);
			break ;
		}
		write(variables -> here_doc, str, ft_strlen(str));
		free(str);
	}
	close_with_check(variables -> here_doc);
}
