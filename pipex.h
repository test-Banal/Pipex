/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:42:23 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/13 10:06:31 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "./libft/libft.h"

typedef struct s_variables
{
	int	f1;
	int	f2;
	int	a;
	int	infile;
	int	outfile;
	int	fd[2];
	int	cc;
}				t_variables;

// void	ft_error_msg(char *msg, int exit_code);
void	ft_error_msg(char *msg, int exit_code, t_variables *variables);


char	*path_finder(char **env);
// char	*true_path(char *argv, char **env);
char	*true_path(char *cmd, char **envp);
void	close_2(int first, int second);
void	close_all(t_variables *variables);
void	fn_path(char **res_split, char *argv);
// void	ft_exec(char **argv, char **args, char **env, int i);
void	piping_m(t_variables *variables, char **argv, char **env, int i);
//void	dup2_2(int first, int second, int third, int fourth);
void	size_check(int argc);
void	open_files(t_variables *variables, char **argv, int argc);
// void	ft_free_split(char **split);
void	ft_pipe(int *fd, t_variables *variables);

#endif
