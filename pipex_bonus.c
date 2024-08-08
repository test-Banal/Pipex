/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:46:41 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/08 17:03:10 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <errno.h>
int	open_files_check(t_variables *variables, char **argv, int argc)
{
	if (here_doc_check(argv[1]))
	{
		here_doc(variables, argv[2]);
		variables -> infile = open("here_doc", O_RDWR, 0777);
		variables -> outfile = open(argv[argc - 1],
				O_RDWR | O_CREAT | O_APPEND, 0777);
	}
	if (!(here_doc_check(argv[1])))
	{
		variables -> infile = open(argv[1], O_RDWR, 0777);
		variables -> outfile = open(argv[argc - 1],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
	}
	if (here_doc_check(argv[1]))
		return (1);
	return (0);
}

void	dup2_b(int first, int second, int third, int fourth)
{
	if (first == -1 || second == -1 || third == -1 || fourth == -1)
		ft_error_msg("Error : open fd\n", -1);
	if (dup2(first, second) == -1)
		ft_error_msg("Error : dup2\n", -1);
	if (dup2(third, fourth) == -1)
		ft_error_msg("Error : dup2\n", -1);
}

void	piping(t_variables *variables, char **argv, char **env, int i)
{
	char	**args;

	variables -> f1 = fork();
	if (variables -> f1 == 0)
	{
		args = ft_split_b(argv[i], ' ');
		if (i == 2)
			dup2_b(variables -> infile, STDIN_FILENO,
				variables -> fd[i - 2][1], STDOUT_FILENO);
		else if (i == 3 && here_doc_check(argv[1]))
			dup2_b(variables -> here_doc, STDIN_FILENO,
				variables -> fd[i - 2][1], STDOUT_FILENO);
		else if (i == variables -> cc)
			dup2_b(variables -> outfile, STDOUT_FILENO,
				variables -> fd[i - 3][0], STDIN_FILENO);
		else
			dup2_b(variables -> fd[i - 2][1], STDOUT_FILENO,
				variables -> fd[i - 3][0], STDIN_FILENO);
		close_all(variables);
		execve(true_path(argv[i], env), args, env);
	}
}

void	ft_error_msg(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	exit(exit_code);
}
void	do_pipes(t_variables *variables)
{
	int	i;

	i = 0;
	while (i < variables -> cc)
		pipe (variables -> fd [i++]);
}

int	main(int argc, char **argv, char **env)
{
	t_variables	variables;
	int			i;

	if (argc < 5)
	{
		perror("Wrong arguments ici");
		exit(1);
	}
	variables.cc = argc - 2;
	i = 2;
	i += open_files_check(&variables, argv, argc);
	do_pipes(&variables);
	while (i < argc - 1)
		piping(&variables, argv, env, i++);
	close_all(&variables);
	while (wait(NULL) != -1)
		;
	unlink("here_doc");
}
