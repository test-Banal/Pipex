/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:46:30 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/22 14:40:50 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_variables *pipex)
{
	char	*buf;

	while (42)
	{
		write(1, " > ", 3);
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL || *buf == '\0')
		{
			write(1, "\n", 1);
			write(1, "pipex: warning - file delimited by end-of-file ", 47);
			write(1, pipex->argv[2], ft_strlen(pipex->argv[2]));
			write(1, "\n", 1);
			break ;
		}
		if (ft_strlen(pipex->argv[2]) == ft_strlen(buf) - 1 && \
			ft_strncmp(pipex->argv[2], buf, ft_strlen(pipex->argv[2])) == 0)
			break ;
		write(pipex->infile, buf, ft_strlen(buf) - 1);
		write(pipex->infile, "\n", 1);
		free(buf);
	}
	free(buf);
}

void	open_here_doc(t_variables *pipex)
{
	pipex->infile = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (pipex->infile == -1)
		ft_putstr_fd(ERR_HEREDOC, 2);
	here_doc(pipex);
	close(pipex->infile);
	pipex->infile = open(".here_doc", O_RDONLY);
	if (pipex->infile == -1)
	{
		unlink(".here_doc");
		ft_putstr_fd(ERR_HEREDOC, 2);
	}
	pipex->outfile = open(pipex->argv[pipex->size + 3],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipex->outfile == -1)
		ft_putstr_fd(ERR_OUT, 2);
}
