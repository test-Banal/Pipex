/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:47:53 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/22 13:47:09 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_command(t_variables *pipex, char *command, int i)
{
	if (!command)
		return (false);
	printf("is_command command: %s\n", command);
	if (access(command, F_OK) == 0 && ft_strncmp(command, "/", 1) == 0)
	{
		pipex->cmds[i].path = ft_strdup(command);
		if (!pipex->cmds[i].path)
			return (false);
		free(command);
		pipex->cmds[i].found = true;
		return (true);
	}
	free(command);
	return (false);
}

void	find_command(t_variables *pipex, int i)
{
	char	*command;
	int		j;

	if (pipex->cmds[i].args[0]
		&& is_command(pipex, ft_strdup(pipex->cmds[i].args[0]), i))
		return ;
	j = 0;
	if (!pipex->paths)
		return (ft_cmd_not_found(pipex, i));
	while (pipex->paths[j])
	{
		command = ft_strjoin3(pipex->paths[j],
				"/", pipex->cmds[i].args[0]);
		printf("command: %s\n", command);
		if (is_command(pipex, command, i))
			break ;
		j++;
		if (!pipex->paths[j])
			ft_cmd_not_found(pipex, i);
	}
}

void	ft_find_path(t_variables *pipex)
{
	int	i;

	i = 0;
	if (!pipex->envp)
		return ;
	while (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH", 4) != 0)
		i++;
	if (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH", 4) == 0)
		pipex->paths = ft_split(pipex->envp[i] + 5, ':');
}

void	open_files(t_variables *pipex)
{
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		ft_putstr_fd(ERR_IN, 2);
	pipex->outfile = open(pipex->argv[pipex->size + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile == -1)
		ft_putstr_fd(ERR_OUT, 2);
}

bool	parse_input(t_variables *pipex)
{
	int	i;

	ft_find_path(pipex);
	if (pipex->heredoc)
		open_here_doc(pipex);
	else
		open_files(pipex);
	i = 0;
	while (i < pipex->size)
	{
		pipex->cmds[i].found = false;
		pipex->cmds[i].args = \
			ft_split(pipex->argv[i + 2 + pipex->heredoc], ' ');
		if (!pipex->cmds[i].args)
			return (false);
		if (!(i == 0 && pipex->infile == -1)
			&& !(i == pipex->size - 1 && pipex->outfile == -1))
			find_command(pipex, i);
		i++;
	}
	return (true);
}
