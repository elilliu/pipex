/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:24:18 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/18 17:54:26 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child(t_pipex *pipex, char **envp, int i)
{
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execve(pipex->args[i][0], pipex->args[i], envp);
}

void	middle_child(t_pipex *pipex, char **envp, int i)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execve(pipex->args[i][0], pipex->args[i], envp);
}

void	last_child(t_pipex *pipex, char **envp, int i)
{
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execve(pipex->args[i][0], pipex->args[i], envp);
}
