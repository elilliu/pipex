/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:18:46 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/18 17:55:00 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_tab(char **tab)
{
	int	row;

	row = 0;
	while (tab[row])
		free(tab[row++]);
	free(tab);
}

void	close_files(t_pipex *pipex)
{
	close(pipex->in_fd);
	close(pipex->out_fd);
}

char	*join(char *path, char *name)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, name);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (str);
}

void	ft_free_args(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nb)
		ft_free_tab(pipex->args[i++]);
}
