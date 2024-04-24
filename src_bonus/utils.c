/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:18:46 by elilliu           #+#    #+#             */
/*   Updated: 2024/04/24 17:22:06 by elilliu          ###   ########.fr       */
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

void	invalid_arguments(void)
{
	ft_putstr_fd("Invalid number of arguments\n", 2);
}

void	error_mess(void)
{
	char	*str;

	str = "Error";
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_cmd(void)
{
	ft_putstr_fd("command not found\n", 2);
	exit(EXIT_FAILURE);
}
