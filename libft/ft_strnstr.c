/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:37:24 by elilliu           #+#    #+#             */
/*   Updated: 2023/11/10 21:36:37 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)big;
	i = 0;
	if (!little[i])
		return (str);
	if (len < 1)
		return (0);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}
