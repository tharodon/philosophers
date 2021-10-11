/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:33:24 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:33:25 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*r;

	i = 0;
	r = (char *)s;
	if (n != 0)
	{
		while (i < n)
			r[i++] = '\0';
	}
}

void	*ft_calloc(size_t n, size_t len)
{
	char	*r;

	r = (char *)malloc(len * n);
	if (r == NULL)
		return (NULL);
	ft_bzero(r, len * n);
	return (r);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	schet(int i, int temp, const char *str)
{
	while (str[i] <= '9' && str[i] >= '0')
	{
		temp = (temp * 10) + (str[i] - 48);
		i++;
	}
	return (temp);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		temp;
	int		minus;

	temp = 0;
	i = 0;
	minus = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
	{
		if (str[i + 1] == '-')
			return (temp);
		i++;
	}
	if (str[i] == '-')
	{
		minus++;
		i++;
	}
	temp = schet(i, temp, str);
	if (minus == 1)
		temp = temp * -1;
	return (temp);
}
