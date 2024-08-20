/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:42:23 by aneumann          #+#    #+#             */
/*   Updated: 2024/08/20 16:11:39 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <fcntl.h>		
# include <stdlib.h>	
# include <stdio.h>		
# include <string.h>	
# include <unistd.h>	
# include <sys/wait.h>	
# include <stdbool.h>	
# include <errno.h>		
# include <error.h>

# define ERR_ARG_1 	"Error: Wrong number of arguments\n"
# define ERR_ARG_2 	"Error: Not enough arguments\n"
# define ERR_IN 	"Error: infile undefined\n"
# define ERR_OUT	"Error: outfile undefined\n"

typedef struct s_cmd
{
	bool	found;
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_variables
{
	int		size;
	int		infile;
	int		outfile;
	t_cmd	*cmds;
	int		**pipes;
	char	**paths;
	char	**argv;
	char	**envp;
	int		*child_pids;
	bool	heredoc;
	int		exitcode;
}				t_variables;


void	redirect(t_variables pipex, int input, int output);
void	children(t_variables pipex, int i);
void	child(t_variables pipex, int i, int input, int output);

void	error_message(char *file);
void	cmd_not_found(t_variables *pipex, int i);

bool	close_all_fds(t_variables *pipex);
bool	free_pipex(t_variables *pipex);
bool	free_array(char **array);

void	open_here_doc(t_variables *pipex);
void	here_doc(t_variables *pipex);

int		main(int argc, char **argv, char **envp);
bool	pipex_init(t_variables *pipex, int argc, char **argv, char **envp);
bool	init_cmds(t_variables *pipex);

bool	is_command(t_variables *pipex, char *command, int i);
void	find_command(t_variables *pipex, int i);
void	find_paths(t_variables *pipex);
void	open_files(t_variables *pipex);
bool	parse_input(t_variables *pipex);

bool	create_pipes(t_variables *pipex);
bool	wait_pids(t_variables *pipex);
bool	allocate_pids(t_variables *pipex);
bool	execute(t_variables *pipex);

#endif
