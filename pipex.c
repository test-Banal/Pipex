/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:47:17 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/29 19:57:57 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

/**
 * Opens the input and output files specified in the command line arguments.
 * 
 * @param variables - a pointer to the t_variables struct that holds file descriptors
 * @param argv - the command line arguments
 * @param argc - the number of command line arguments
 */
void open_files(t_variables *variables, char **argv, int argc)
{
	variables->infile = open(argv[1], O_RDONLY, 0);
	if (variables->infile == -1)
	{
		close(variables->infile);
		ft_error_msg("Error opening infile", 1);
	}
	variables->outfile = open(argv[argc - 1],
							  O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (variables->outfile == -1)
	{
		close(variables->infile);
		ft_error_msg("Error opening outfile", 1);
	}
}

/**
 * Checks if the number of command line arguments is correct.
 * 
 * @param argc - the number of command line arguments
 */
void size_check(int argc)
{
	if (argc != 5)
	{
		perror("Wrong arguments : ./pipex infile cmd1 cmd2 outfile");
		exit(0);
	}
}

/**
 * Checks if the file descriptors are valid and duplicates them if necessary.
 * 
 * @param fd1 - the first file descriptor
 * @param fd2 - the second file descriptor
 */
void dup2_check(int fd1, int fd2)
{
	if (fd1 == -1)
		ft_error_msg("Error opening file", 1);
	if (fd2 == -1)
		ft_error_msg("Error opening file", 2);
	if (dup2(fd1, fd2) == -1)
		ft_error_msg("Error duplicating file descriptor", 1);
}

/**
 * Executes the command specified in the command line arguments.
 * 
 * @param variables - a pointer to the t_variables struct that holds file descriptors
 * @param argv - the command line arguments
 * @param env - the environment variables
 * @param i - the index of the command in the command line arguments
 */
void exec_command(t_variables *variables, char **argv, char **env, int i)
{
	char **args = ft_split(argv[i], ' ');

	if (i == 2)
	{
		dup2_check(variables->infile, STDIN_FILENO);
		dup2_check(variables->fd[1], STDOUT_FILENO);
	}
	else if (i == 3)
	{
		dup2_check(variables->outfile, STDOUT_FILENO);
		dup2_check(variables->fd[0], STDIN_FILENO);
	}

	close_all(variables);
	execve(true_path(argv[i], env), args, env);

	if (errno == ENOENT)
		ft_error_msg("Error executing command", 127);
	else
		ft_error_msg("Error executing command", 1);

	// Free memory allocated by ft_split if necessary
	ft_free_split(args);
}

/**
 * Creates a child process and executes the command specified in the command line arguments.
 * 
 * @param variables - a pointer to the t_variables struct that holds file descriptors
 * @param argv - the command line arguments
 * @param env - the environment variables
 * @param i - the index of the command in the command line arguments
 */
void piping(t_variables *variables, char **argv, char **env, int i)
{
	variables->f1 = fork();
	if (variables->f1 == 0)
	{
		exec_command(variables, argv, env, i);
	}
	else if (variables->f1 == -1)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}
}

/**
 * Creates a pipe.
 * 
 * @param fd - an array to store the file descriptors of the pipe
 */
void ft_pipe(int *fd)
{
	pipe(fd);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

/**
 * The main function of the program.
 * 
 * @param argc - the number of command line arguments
 * @param argv - the command line arguments
 * @param env - the environment variables
 * @return 0 on success, non-zero value on failure
 */
int main(int argc, char **argv, char **env)
{
	t_variables variables;
	int i;

	variables.cc = argc - 3;
	i = 2;
	size_check(argc);
	open_files(&variables, argv, argc);
	ft_pipe(variables.fd);
	while (i < 4)
		piping(&variables, argv, env, i++);
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
