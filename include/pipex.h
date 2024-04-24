/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:04:54 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/24 17:14:56 by elilliu          ###   ########.fr       */
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
	int		fd[2];
	int		pid;
}				t_pipex;

int		main(int ac, char **av, char **env);
void	first_child(t_pipex *pipex, char *infile, char *av, char **env);
void	middle_child(t_pipex *pipex, char *av, char **env);
void	last_child(t_pipex *pipex, char *outfile, char *av, char **env);
void	exec_cmd(char *av, char **env);
void	invalid_arguments(void);
void	error_mess(void);
void	error_cmd(void);
void	ft_free_tab(char **tab);
char	*join(char *path, char *name);

#endif
