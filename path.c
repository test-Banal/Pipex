/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:47:53 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/29 19:09:45 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_finder(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = "PATH=";
	while (env[i])
	{
		if (*env[i] == 'P')
		{
			if (!(ft_strncmp(env[i], path, 5)))
				path = env[i];
		}
		i++;
	}
	return (path);
}

char	*true_path(char *argv, char **env)
{
	int				i;
	char			**res_split;
	char			**args;
	char			*path;

	if (access(argv, F_OK) == 0)
		return (argv);
	if (ft_strchr (argv, '/') != NULL)
		ft_error();
	path = "PATH=";
	args = ft_split(argv, ' ');
	path = path_finder(env);
	i = 0;
	res_split = ft_split(path, ':');
	fn_path(res_split, args[0]);
	while (res_split[i++])
	{
		if (access(res_split[i], F_OK) == 0)
		{
			if (access(res_split[i], X_OK) == 0)
				return (res_split[i]);
			else
				ft_error_msg("Permission denied", 126);
		}
	}
	ft_error_msg("Command not found", 127);
	return (NULL);
}

void	close_2(int first, int second)
{
	if (first == -1 || second == -1)
	{
		perror("Failed close");
		exit(0);
	}
	close(first);
	close(second);
}

void	close_all(t_variables *variables)
{
	close(variables -> outfile);
	close(variables -> infile);
	close(variables -> fd[1]);
	close(variables -> fd[0]);
}

void	fn_path(char **res_split, char *argv)
{
	int	i;

	i = 0;
	while (res_split[i])
	{
		res_split[i] = ft_strjoin(res_split[i], "/");
		res_split[i] = ft_strjoin(res_split[i], argv);
		i++;
	}
}
