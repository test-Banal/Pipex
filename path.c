/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:47:53 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/08 16:17:37 by aneumann         ###   ########.fr       */
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

char	*true_path(char *argv, char **env, t_variables *variables) //rajouter variables
{
	int				i;
	char			**res_split;
	char			**args;
	char			*path;

	if (access(argv, F_OK) == 0)
		return (argv);
	if (ft_strchr (argv, '/') != NULL)
	{
		printf("OEOE\n");
		ft_error();
	}
	path = "PATH=";
	args = ft_split_b(argv, ' ');
	path = path_finder(env);
	i = 0;
	res_split = ft_split_b(path, ':');
	fn_path(res_split, args[0]);
	while (res_split[i++])
	{
		if (access(res_split[i], F_OK) == 0)
		{
			if (access(res_split[i], X_OK) == 0)
				return (res_split[i]);
			else
				return (ft_error_msg("Permission denied\n", 126, variables), NULL);
		}
	}
	free(res_split);
	free(args);
	return (NULL);
}

void	close_2(int first, int second)
{
	if (first == -1 || second == -1)
	{
		perror("Failed close");
		exit(10);
	}
    if (first != -1)
        close(first);
    if (second != -1)
        close(second);
}

void	close_all(t_variables *variables)
{
	printf("BEFORE CLOSE\nfd outfile = %d\nfdinfile = %d\nfd1 = %d\nfd2 = %d\n", variables->outfile, variables->infile, variables->fd[1], variables->fd[0]);

    if (variables->outfile >= 0) {
        close(variables->outfile);
        variables->outfile = -1;
    }
    if (variables->infile >= 0) {
        close(variables->infile);
        variables->infile = -1;
    }
    if (variables->fd[1] >= 0) {
        close(variables->fd[1]);
        variables->fd[1] = -1;
    }
    if (variables->fd[0] >= 0) {
        close(variables->fd[0]);
        variables->fd[0] = -1;
    }
	printf("AFTER CLOSE\nfd outfile = %d\nfdinfile = %d\nfd1 = %d\nfd2 = %d\n", variables->outfile, variables->infile, variables->fd[1], variables->fd[0]);

}
// {
// 	printf("BEFORE CLOSE\nfd outfile = %d\nfdinfile = %d\nfd1 = %d\nfd2 = %d\n", variables->outfile, variables->infile, variables->fd[1], variables->fd[0]);
// 	close(variables->outfile);
// 	close(variables->infile);
// 	close(variables->fd[1]);
// 	close(variables->fd[0]);
// 	printf("AFTER CLOSE\nfd outfile = %d\nfdinfile = %d\nfd1 = %d\nfd2 = %d\n", variables->outfile, variables->infile, variables->fd[1], variables->fd[0]);
// }


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
