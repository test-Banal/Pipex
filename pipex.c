/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:47:17 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/30 17:30:55 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_variables *variables, char **argv, int argc)
{
	variables->infile = open(argv[1], O_RDONLY, 0);
	if (variables->infile == -1)
	{
		close(variables->infile);
		ft_error_msg("Error opening infile\n", 0);
	}
	variables->outfile = open(argv[argc - 1],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (variables->outfile == -1)
	{
		close(variables->infile);
		ft_error_msg("Error opening outfile", 1);
	}
}

void	size_check(int argc)
{
	if (argc != 5)
	{
		perror("Wrong arguments: ./pipex infile cmd1 cmd2 outfile\n");
		exit(0);
	}
}

void	dup2_check(int fd1, int fd2)
{
	if (fd1 == -1 || fd2 == -1)
	{
		perror("open");
		exit(0);
	}
	dup2(fd1, fd2);
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		exit(0);
	}
}

// void	ft_exec(char **argv, char **args, char **env, int i)
// {
// 	execve(true_path(argv[i], env), args, env);
// 	if (execve(true_path(argv[i], env), args, env) == -1)
// 	{
// 		perror("Error execve");
// 		exit(0);
// 	}
// }

void	piping_m(t_variables *variables, char **argv, char **env, int i)
{
	char	**args;

	variables -> f1 = fork();
	if (variables -> f1 == 0)
	{
		if (i == 2)
		{
			dup2_check(variables -> infile, STDIN_FILENO);
			dup2_check(variables -> fd[1], STDOUT_FILENO);
			args = ft_split_b(argv[i], ' ');
			close_all(variables);
			// ft_exec(argv, args, env,1);
			execve(true_path(argv[i], env), args, env);	
		}
		else if (i == 3)
		{
			dup2_check(variables -> outfile, STDOUT_FILENO);
			dup2_check(variables -> fd[0], STDIN_FILENO);
			args = ft_split_b(argv[i], ' ');
			close_all(variables);
			// ft_exec(argv, args, env, 1);
			execve(true_path(argv[i], env), args, env);
		}
	}
}

void	ft_pipe(int *fd)
{
	pipe(fd);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_variables	variables;
	int		i;

	variables.cc = argc - 3;
	i = 2;
	size_check(argc);
	open_files(&variables, argv, argc);
	ft_pipe(&variables.fd[0]);
	while (i < 4)
		piping_m(&variables, argv, env, i++);
	close_2(variables.infile, variables.outfile);
	close_2(variables.fd[1], variables.fd[0]);
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
