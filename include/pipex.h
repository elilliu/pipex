/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:04:54 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/18 17:54:44 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		cmd_nb;
	int		in_fd;
	int		out_fd;
	int		fd[2];
	int		pid;
	char	**poss_paths;
	char	***args;
}				t_pipex;

int		main(int ac, char **av, char **env);
void	error_mess(void);
void	close_files(t_pipex *pipex);
void	ft_free_tab(char **tab);
void	ft_free_args(t_pipex *pipex);
void	ft_clean_all(t_pipex *pipex);
char	*join(char *path, char *name);
int		init_args(char **av, t_pipex *pipex);
int		absolute_paths(t_pipex *pipex);
int		all_paths(char **env, t_pipex *pipex);
int		relative_paths(t_pipex *pipex);
void	first_child(t_pipex *pipex, char **envp, int i);
void	middle_child(t_pipex *pipex, char **envp, int i);
void	last_child(t_pipex *pipex, char **envp, int i);
void	error_cmd(void);
void	invalid_arguments(void);

#endif
