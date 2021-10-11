/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 05:01:14 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 05:01:16 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

char	*ft_substr(char const *s, int start, int len)
{
	int		b;
	char	*r;

	b = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen((char *)s))
	{
		r = ft_calloc(1, sizeof(char *));
		return (r);
	}
	if (len > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	r = (char *)malloc(len + 1);
	if (r == NULL)
		return (NULL);
	r[len] = '\0';
	while (len--)
		r[len] = s[start + len];
	return (r);
}
