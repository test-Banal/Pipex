/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:00:55 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/20 16:00:57 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect(t_variables pipex, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	close(output);
}

void	children(t_variables pipex, int i)
{
	if (!pipex.cmds[i].found)
	{
		close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	if (i == 0)
		child(pipex, i, pipex.infile, pipex.pipes[i][1]);
	else if (i != pipex.size - 1)
		child(pipex, i, pipex.pipes[i - 1][0], pipex.pipes[i][1]);
	else
		child(pipex, i, pipex.pipes[i - 1][0], pipex.outfile);
}

void	child(t_variables pipex, int i, int input, int output)
{
	redirect(pipex, input, output);
	close_all_fds(&pipex);
	if (execve(pipex.cmds[i].path, pipex.cmds[i].args, pipex.envp) == -1)
	{
		free_pipex(&pipex);
		error_message(NULL);
	}
	exit(1);
}
