/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:58:41 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/26 18:06:54 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd_not_found(t_variables *pipex, int i)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(pipex->cmds[i].args[0], 2);
	ft_putstr_fd("\n", 2);
	pipex->cmds[i].found = false;
}

bool	ft_close_all_fds(t_variables *pipex)
{
	int	i;

	i = 0;
	if (!pipex->pipes)
		return (false);
	while (i < pipex->size && pipex->pipes[i])
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		if (pipex->pipes[i])
			free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	return (true);
}

bool	free_pipex(t_variables *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size && pipex->cmds && pipex->cmds[i].args)
	{
		free_array(pipex->cmds[i].args);
		if (pipex->cmds[i].found)
			free(pipex->cmds[i].path);
		i++;
	}
	free(pipex->cmds);
	if (pipex->paths)
		free_array(pipex->paths);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->child_pids)
		free(pipex->child_pids);
	if (pipex->heredoc)
		unlink(".here_doc");
	return (true);
}

bool	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (false);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (true);
}
