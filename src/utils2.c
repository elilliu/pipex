/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:21:44 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/19 15:19:38 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_clean_all(t_pipex *pipex)
{
	ft_free_args(pipex);
	free(pipex->args);
	close_files(pipex);
}

void	invalid_arguments(void)
{
	ft_putstr_fd("Invalid number of arguments\n", 2);
}

void	error_mess(void)
{
	char	*str;

	str = "Error";
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_cmd(void)
{
	ft_putstr_fd("command not found\n", 2);
}
