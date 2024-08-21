/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:58:53 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/21 16:19:49 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_variables	pipex;

	if (argc != 5)
	{
		ft_putstr_fd(ERR_ARG_1, 2);
		return (EXIT_FAILURE);
	}
	if (!ft_init(&pipex, argc, argv, envp))
		return (free_pipex(&pipex), \
			ft_putstr_fd("Error init\n", 2), EXIT_FAILURE);
	if (!parse_input(&pipex))
		return (free_pipex(&pipex), EXIT_FAILURE);
	if (!ft_create_pipes(&pipex))
		return (free_pipex(&pipex), \
			ft_putstr_fd("Error pipe\n", 2), EXIT_FAILURE);
	if (!ft_execute(&pipex))
		return (free_pipex(&pipex), \
			ft_putstr_fd("Error\n", 2), pipex.exitcode);
	free_pipex(&pipex);
	return (pipex.exitcode);
}

bool	ft_init(t_variables *pipex, int argc, char **argv, char **envp)
{
	pipex->paths = NULL;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmds = NULL;
	pipex->pipes = NULL;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->child_pids = NULL;
	pipex->exitcode = EXIT_SUCCESS;
	pipex->heredoc = false;
	pipex->size = argc - 3;
	if (!ft_init_cmds(pipex))
		return (false);
	return (true);
}

bool	ft_init_cmds(t_variables *pipex)
{
	int	i;

	pipex->cmds = malloc(pipex->size * sizeof(t_cmd));
	if (!pipex->cmds)
		return (false);
	i = 0;
	while (i < pipex->size)
	{
		pipex->cmds[i].args = NULL;
		pipex->cmds[i].found = false;
		pipex->cmds[i].path = NULL;
		i++;
	}
	return (true);
}
