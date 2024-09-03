/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:42:23 by aneumann          #+#    #+#             */
/*   Updated: 2024/09/02 15:33:00 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <fcntl.h>		
# include <stdlib.h>	//
# include <stdio.h>		//
# include <string.h>	
# include <unistd.h>	//
# include <sys/wait.h>	//
# include <stdbool.h>	//
# include <errno.h>		
# include <error.h>

# define ERR_ARG_1 	"Error: Wrong number of arguments\n"
# define ERR_ARG_2 	"Error: Not enough arguments\n"
# define ERR_IN 	"Error: infile\n"
# define ERR_OUT	"Error: outfile\n"
# define ERR_HEREDOC	"Error: here_doc\n"

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

void	ft_redirect(t_variables pipex, int input, int output);
void	ft_children(t_variables pipex, int i);
void	ft_child(t_variables pipex, int i, int input, int output);

void	ft_cmd_not_found(t_variables *pipex, int i);

bool	ft_close_all_fds(t_variables *pipex);
bool	free_pipex(t_variables *pipex);
bool	free_array(char **array);

void	open_here_doc(t_variables *pipex);
void	here_doc(t_variables *pipex);

int		main(int argc, char **argv, char **envp);
bool	ft_init(t_variables *pipex, int argc, char **argv, char **envp);
bool	ft_init_cmds(t_variables *pipex);

bool	is_command(t_variables *pipex, char *command, int i);
void	find_command(t_variables *pipex, int i);
void	ft_find_path(t_variables *pipex);
void	open_files(t_variables *pipex);
bool	parse_input(t_variables *pipex);

bool	ft_create_pipes(t_variables *pipex);
bool	ft_wait_pids(t_variables *pipex);
bool	ft_allocate_pids(t_variables *pipex);
bool	ft_execute(t_variables *pipex);

#endif
