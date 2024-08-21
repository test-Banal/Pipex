/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:46:41 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/21 16:20:17 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_variables	pipex;

	if (argc < 5)
		return (ft_putstr_fd(ERR_ARG_2, 2), EXIT_FAILURE);
	if (!ft_init(&pipex, argc, argv, envp))
		return (free_pipex(&pipex), \
			ft_putstr_fd("Pipex : Error init\n", 2), EXIT_FAILURE);
	if (argc < 5 + pipex.heredoc)
		return (ft_putstr_fd(ERR_ARG_2, 2), free_pipex(&pipex), EXIT_FAILURE);
	if (!parse_input(&pipex))
		return (free_pipex(&pipex), EXIT_FAILURE);
	if (!ft_create_pipes(&pipex))
		return (free_pipex(&pipex), \
			ft_putstr_fd("Pipex : Error pipe\n", 2), EXIT_FAILURE);
	if (!ft_execute(&pipex))
		return (free_pipex(&pipex), \
			ft_putstr_fd("Pipex : Error ", 2), pipex.exitcode);
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
	if (ft_strncmp(pipex->argv[1], "here_doc", 9) == 0
		&& ft_strncmp(pipex->argv[0], "./pipex", 14) == 0)
		pipex->heredoc = true;
	pipex->size = argc - 3 - pipex->heredoc;
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
