/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:55:03 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/24 18:11:41 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child(t_pipex *pipex, char *infile, char *av, char **env)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		error_mess();
	dup2(fd, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(fd);
	close(pipex->fd[0]);
	close(pipex ->fd[1]);
	exec_cmd(av, env);
}

void	middle_child(t_pipex *pipex, char *av, char **env)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	exec_cmd(av, env);
}

void	last_child(t_pipex *pipex, char *outfile, char *av, char **env)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_mess();
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	exec_cmd(av, env);
}
