/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:32 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/18 15:11:49 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	d;
	int	exit_code;

	if (argc < 5)
	{
		if (argc > 2 && !ft_strncmp("here_doc", argv[1], 9))
			return (ft_msg_error("Error: ",
				"./pipex here_doc LIMITER cmd1 cmd2 file2", "", 1));
		return (ft_msg_error("Error: ",
			"./pipex file1 cmd1 ... cmdn file2", "", 1));
	}
	else if (argc < 6 && !ft_strncmp("here_doc", argv[1], 9))
		return(ft_msg_error("Error: ", "./pipex here_doc LIMITER
			cmd1 cmd2 file2", "", 1);
	if (!envp || envp[0][0] == '\0')
		ft_exit_error(ft_msg_error("Unexpected error.", "", "", 1), &d);
	d = ft_init(argc, argv, envp);
	ft_exit_code = pipex(&d);
	return (exit_code);
}

