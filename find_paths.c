/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:56:53 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/16 14:53:08 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	absolute_paths(t_pipex *pipex)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < pipex->cmd_nb)
	{
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

char	*new_path(t_pipex *pipex, char *str)
{
	char	*newstr;
	int		i;

	i = 0;
	while (pipex->poss_paths[i])
	{
		newstr = join(pipex->poss_paths[i], str);
		if (!newstr)
			return (NULL);
		if (access(newstr, F_OK | X_OK) == 0)
			return (newstr);
		free(newstr);
		i++;
	}
	return (NULL);
}

int	relative_paths(t_pipex *pipex)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < pipex->cmd_nb)
	{
		if (access(pipex->args[i][0], F_OK | X_OK) != 0)
		{
			tmp = new_path(pipex, pipex->args[i][0]);
			if (!tmp)
				return (0);
			free(pipex->args[i][0]);
			pipex->args[i][0] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (1);
}
