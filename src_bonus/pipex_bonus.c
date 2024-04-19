/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:04 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/19 15:24:50 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	verif_files(int ac, char **av, t_pipex *pipex)
{
	pipex->in_fd = open(av[1], O_RDONLY);
	if (pipex->in_fd == -1)
		return (error_mess(), 0);
	pipex->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd == -1)
		return (close(pipex->in_fd), error_mess(), 0);
	return (1);
}

int	init_args(char **av, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->args = malloc(sizeof(char **) * (pipex->cmd_nb + 1));
	if (!pipex->args)
		return (0);
	while (i < pipex->cmd_nb)
	{
		pipex->args[i] = ft_split(av[i + 2], ' ');
		if (!pipex->args[i])
		{
			while (i >= 0)
				ft_free_tab(pipex->args[i--]);
			free(pipex->args);
			return (0);
		}
		i++;
	}
	return (1);
}

void	which_child(t_pipex *pipex, char **env, int i)
{
	if (i == 0)
		first_child(pipex, env, i);
	else if (i == pipex->cmd_nb - 1)
		last_child(pipex, env, i);
	else
		middle_child(pipex, env, i);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	exec_child(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nb)
	{
		if (pipe(pipex->fd) == -1)
			return (ft_clean_all(pipex), error_mess(), 0);
		pipex->pid = fork();
		if (pipex->pid == -1)
			return (ft_clean_all(pipex), error_mess(), 0);
		if (pipex->pid == 0)
			which_child(pipex, env, i);
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

	if (ac < 5)
		return (invalid_arguments(), 1);
	pipex.cmd_nb = ac - 3;
	verif_files(ac, av, &pipex);
	if (init_args(av, &pipex) == 0)
		return (close_files(&pipex), error_mess(), 1);
	if (absolute_paths(&pipex) == 0)
	{
		if (all_paths(env, &pipex) == 0)
			return (ft_clean_all(&pipex), error_mess(), 1);
		if (!pipex.poss_paths)
			return (ft_clean_all(&pipex), error_cmd(), 1);
		if (relative_paths(&pipex) == 0)
			return (ft_clean_all(&pipex), ft_free_tab(pipex.poss_paths),
				error_cmd(), 1);
		ft_free_tab(pipex.poss_paths);
	}
	exec_child(&pipex, env);
	ft_clean_all(&pipex);
	return (0);
}
