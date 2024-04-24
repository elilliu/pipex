/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:42:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/24 17:49:51 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	which_child(t_pipex *pipex, char **av, char **env, int i)
{
	if (i == 0)
		first_child(pipex, av[1], av[i + 2], env);
	else if (i == pipex->cmd_nb - 1)
		last_child(pipex, av[pipex->cmd_nb + 2], av[i + 2], env);
	else
		middle_child(pipex, av[i + 2], env);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	exec_child(t_pipex *pipex, char **av, char **env)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nb)
	{
		if (pipe(pipex->fd) == -1)
			return (error_mess(), 0);
		pipex->pid = fork();
		if (pipex->pid == -1)
			return (error_mess(), 0);
		if (pipex->pid == 0)
			which_child(pipex, av, env, i);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		i++;
	}
	while (wait(NULL) != -1)
		continue ;
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	pipex.cmd_nb = ac - 3;
	if (ac < 5)
		return (invalid_arguments(), 1);
	exec_child (&pipex, av, env);
}
