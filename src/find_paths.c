/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:56:53 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/19 15:22:39 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	absolute_paths(t_pipex *pipex)
{
	int		i;

	i = 0;
	while (i < pipex->cmd_nb)
	{
		if (!pipex->args[i][0])
			return (0);
		if (access(pipex->args[i][0], F_OK | X_OK) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	all_paths(char **env, t_pipex *pipex)
{
	char	*str;
	int		i;

	i = 0;
	if (!env[i])
		return (0);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			str = ft_strtrim(env[i], "PATH=");
			if (!str)
				return (0);
			pipex->poss_paths = ft_split(str, ':');
			if (!pipex->poss_paths)
				return (free(str), 0);
			return (free(str), 1);
		}
		i++;
	}
	return (1);
}

int	new_path(t_pipex *pipex, int i)
{
	char	*newstr;
	int		j;

	j = 0;
	while (pipex->poss_paths[j])
	{
		newstr = join(pipex->poss_paths[j], pipex->args[i][0]);
		if (!newstr)
			return (0);
		if (access(newstr, F_OK | X_OK) == 0)
		{
			free(pipex->args[i][0]);
			pipex->args[i][0] = ft_strdup(newstr);
			if (!pipex->args[i][0])
				return (0);
			return (free(newstr), 1);
		}
		free(newstr);
		j++;
	}
	return (-1);
}

int	relative_paths(t_pipex *pipex)
{
	int	i;
	int	newpath;

	i = 0;
	while (i < pipex->cmd_nb)
	{
		if (!pipex->args[i][0])
			error_cmd();
		else if (access(pipex->args[i][0], F_OK | X_OK) != 0)
		{
			newpath = new_path(pipex, i);
			if (newpath == 0)
				return (0);
			else if (newpath == -1)
				error_cmd();
		}
		i++;
	}
	return (1);
}
