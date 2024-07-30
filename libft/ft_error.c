/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneumann <aneumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:50:57 by aneumann          #+#    #+#             */
/*   Updated: 2024/07/30 15:41:52 by aneumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(void)
{
	perror("Error");
	exit(0);
}

void	ft_error_msg(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	exit(exit_code);
}
