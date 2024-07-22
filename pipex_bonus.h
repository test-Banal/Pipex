/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:46:54 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/22 16:18:51 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int	here_doc;
	int	fd[1000][2];
	int	cc;
}				t_variables;





#endif
