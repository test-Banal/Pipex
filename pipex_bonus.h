/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:46:54 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/30 14:53:41 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int	here_doc;
	int	fd[1000][2];
	int	cc;
}				t_variables;

int		here_doc_check(char *argv);
void	close_with_check(int fd);
void	here_doc(t_variables *variables, char *lim);
char	*path_finder(char **env);
void	fn_path_b(char **res_split, char *argv);
char	*true_path(char *argv, char **env);
void	close_all(t_variables *variables);
int		open_files_check(t_variables *variables, char **argv, int argc);
void	dup2_b(int first, int second, int third, int fourth);
void	piping(t_variables *variables, char **argv, char **env, int i);
void	do_pipes(t_variables *variables);

#endif
