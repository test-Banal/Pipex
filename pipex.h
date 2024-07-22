/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:42:23 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/22 16:19:00 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

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



#endif
