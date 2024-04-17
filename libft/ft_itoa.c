/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:50:46 by elilliu           #+#    #+#             */
/*   Updated: 2023/11/09 18:40:17 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int n)
{
	int				len;
	unsigned int	nb;

	if (n >= 0)
	{
		len = 1;
		nb = n;
	}
	else
	{
		len = 2;
		nb = -n;
	}
	while ((nb / 10) > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*str;
	int				i;
	int				len;

	len = ft_len(n);
	nb = n;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		i++;
		nb = -nb;
	}
	str[len--] = '\0';
	while (len >= i)
	{
		str[len] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (str);
}
