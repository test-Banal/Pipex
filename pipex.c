/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:47:17 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/19 08:42:05 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_msg(char *msg, int exit_code, t_variables *variables)
{
	ft_putstr_fd(msg, 2);
	close_all(variables);
	exit(exit_code);
}

void	open_files(t_variables *variables, char **argv, int argc)
{
	variables->infile = open(argv[1], O_RDONLY, 0);
	if (variables->infile == -1)
	{
		ft_error_msg("Error opening infile : No such file or directory\n", 1, variables);
	}
	variables->outfile = open(argv[argc - 1],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (variables->outfile == -1)
	{
		ft_error_msg("Error opening outfile : No such file or directory\n", 1, variables);
	}
}

void	size_check(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Wrong arguments: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(0);
	}
}

void	dup2_check(int fd1, int fd2)
{
	if (fd1 == -1 || fd2 == -1)
	{
		ft_putstr_fd(" Error : open fd\n", 2);
		exit(-1);
	}
	if (dup2(fd1, fd2) == -1)
	{
		ft_putstr_fd("Error : dup2\n", 2);
		exit(-1);
	}
}

static void	ft_exec(char **argv, char **args, char **env, int i, t_variables *variables) //rajouter variables
{
	char	*path;
	if (i == 2 || i == 3)
	{
		path = true_path(argv[i], env); //rajouter variables
		if (path == NULL)
		{
				int j = -1;
				while (args[++j])
					free(args[j]);
				free(args);
				ft_putstr_fd(argv[i], 2);
				ft_error_msg(": Error:  command not found\n", 127, variables);
		}
		if (execve(path, args, env) == -1)
			ft_error_msg("Error execve\n", 1, variables);
	}
}

void	piping_m(t_variables *variables, char **argv, char **env, int i)
{
	char	**args;

	variables -> f1 = fork();
	if (variables -> f1 == -1)
		ft_error_msg("Error: fork\n", -1, variables);
	if (variables -> f1 == 0)
	{
       args = ft_split_b(argv[i], ' ');
        if (i == 2)
        {
            dup2_check(variables->infile, STDIN_FILENO);
            dup2_check(variables->fd[1], STDOUT_FILENO);
			close(variables->fd[0]);
        }
        else if (i == 3)
        {
			close(variables->fd[1]);
            dup2_check(variables->fd[0], STDIN_FILENO);
            dup2_check(variables->outfile, STDOUT_FILENO);
			close(variables->fd[1]);
        }
        ft_exec(argv, args, env, i, variables);
		exit(0);
    }
}

void	ft_pipe(int *fd, t_variables *variables) //rajouter variables
{
	pipe(fd);
	if (fd[0] == -1 || fd[1] == -1)
		ft_error_msg("Error: pipe\n", -1, variables);
}

int	main(int argc, char **argv, char **env)
{
	t_variables	variables;
	int		i;

	variables.cc = argc - 3;
	i = 2;
	size_check(argc);
	open_files(&variables, argv, argc);
	ft_pipe(&variables.fd[0], &variables);
	while (i < 4)
		piping_m(&variables, argv, env, i++);
	close_all(&variables);
	while (wait(NULL) != -1)
		;
}

// int	main(int argc, char **argv, char **env)
// {
// ...
// ...
// ...
// 	while (waitpid(-1, &status, 0) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			printf("Process exited with status %d\n", WEXITSTATUS(status));
// 		else if (WIFSIGNALED(status))
// 			printf("Process killed by signal %d\n", WTERMSIG(status));
// 	}
// 	if (errno != ECHILD)
// 			ft_error_msg("waitpid", 1);
// 	return (0);
// }
