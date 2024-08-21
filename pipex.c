/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:47:17 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/21 15:58:34 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	ft_create_pipes(t_variables *pipex)
{
	int	i;

	i = 0;
	pipex->pipes = malloc((pipex->size) * sizeof(int *));
	if (!pipex->pipes)
		return (false);
	while (i < pipex->size)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
			return (false);
		if (pipe(pipex->pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

bool	ft_wait_pids(t_variables *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size && pipex->child_pids[i] > 0)
	{
		waitpid(pipex->child_pids[i], NULL, 0);
		i++;
	}
	if (pipex->outfile == -1)
		pipex->exitcode = 1;
	else if (!pipex->cmds[i - 1].found)
		pipex->exitcode = 127;
	else
		pipex->exitcode = 0;
	return (true);
}

bool	ft_allocate_pids(t_variables *pipex)
{
	int	i;

	pipex->child_pids = malloc(pipex->size * sizeof(int));
	if (!pipex->child_pids)
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pipex->child_pids[i] = -1;
		i++;
	}
	return (true);
}

bool	ft_execute(t_variables *pipex)
{
	int	pid;
	int	i;

	if (!ft_allocate_pids(pipex))
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pid = fork();
		if (pid == 0)
			ft_children(*pipex, i);
		else if (pid > 0)
			pipex->child_pids[i] = pid;
		else
			return (ft_close_all_fds(pipex), false);
		i++;
	}
	ft_close_all_fds(pipex);
	ft_wait_pids(pipex);
	return (true);
}
