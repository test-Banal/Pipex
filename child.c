/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:00:55 by aneumann          #+#    #+#             */
/*   Updated: 2024/09/03 16:51:50 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_redirect(t_variables pipex, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		ft_close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		ft_close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	close(output);
}

void	ft_children(t_variables pipex, int i)
{
	if (!pipex.cmds[i].found)
	{
		ft_close_all_fds(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	if (i == 0)
		ft_child(pipex, i, pipex.infile, pipex.pipes[i][1]);
	else if (i != pipex.size - 1)
		ft_child(pipex, i, pipex.pipes[i - 1][0], pipex.pipes[i][1]);
	else
		ft_child(pipex, i, pipex.pipes[i - 1][0], pipex.outfile);
}

void	ft_child(t_variables pipex, int i, int input, int output)
{
	ft_redirect(pipex, input, output);
	ft_close_all_fds(&pipex);
	// 	printf("la	\n");
	// fflush(stdout);  // Force l'affichage immédiat

	// printf("path: %s\n", pipex.cmds[i].path);
	// fflush(stdout);

	// int j = 0;
	// while (pipex.cmds[i].args[j])
	// {
	// 	printf("args[%d]: %s\n", j, pipex.cmds[i].args[j]);
	// 	fflush(stdout);
	// 	j++;
	// }

	// j = 0;
	// while (pipex.envp[j])
	// {
	// 	printf("envp[%d]: %s\n", j, pipex.envp[j]);
	// 	fflush(stdout);
	// 	j++;
	// }
	if (execve(pipex.cmds[i].path, pipex.cmds[i].args, pipex.envp) == -1)
	{
		free_pipex(&pipex);
		ft_putstr_fd("Error execve\n", 2);
		exit(1);
	}
}
