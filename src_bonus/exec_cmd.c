/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:30:53 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/24 18:01:17 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**all_paths(char **env)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	if (!env[i])
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			str = ft_strtrim(env[i], "PATH");
			if (!str)
				return (NULL);
			paths = ft_split(str, ':');
			if (!paths)
				return (free(str), NULL);
			free(str);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*new_path(char *av, char **env)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	paths = all_paths(env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		str = join(paths[i], av);
		if (!str)
			return (ft_free_tab(paths), NULL);
		if (access(str, F_OK | X_OK) == 0)
			return (ft_free_tab(paths), str);
		free(str);
		i++;
	}
	return (ft_free_tab(paths), NULL);
}

void	exec_cmd(char *av, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(av, ' ');
	if (!args)
		error_cmd();
	if (access(args[0], F_OK | X_OK) == 0)
		path = ft_strdup(args[0]);
	else
		path = new_path(args[0], env);
	if (!path)
	{
		ft_free_tab(args);
		error_mess();
	}
	if (execve(path, args, env) == -1)
	{
		ft_free_tab(args);
		free(path);
	}
}
