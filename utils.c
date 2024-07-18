/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:10:09 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/18 15:27:34 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_msg_error(char *str1, char *str2, char *str3, int erno)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	return (erno);
}

void	ft_close_pipe_fd(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->nb_cmds - 1) * 2)
	{
		close(data->pipe[i]);
		i++;
	}
}

void	ft_close_fd(t_data *data)
{
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	ft_close_pipe_fd(data);
}

void	ft_exit_error(int error, t_data *data)
{
	if (data)
	{
		ft_close_fd(data);
		if (data->pipe != NULL)
			free(data->pipe);
		if (data->pids != NULL)
			free(data->pids);
		if (data->cmd_options != NULL || data->cmd_path != NULL)
			ft_free_str(data->cmd_path, data->cmd_options);
	}
	if (data->heredoc == 1)
		unlink(".heredoc.tmp");
	exit(error_status);
}

void	ft_free_str(char *str, char **stro)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (stro != NULL)
	{
		i = 0;
		while (stro[i])
		{
			free(stro[i]);
			i++;
		}
		free(stro);
		stro = NULL;
	}
}
