/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:32:12 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:32:14 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

static char	*jango(char **j, size_t i)
{
	while (i >= 0 && j[i])
	{
		free(j[i]);
		i--;
	}
	free(j);
	return (NULL);
}

static size_t	schet(char const *s, char c)
{
	size_t	i;
	size_t	sep;

	i = 0;
	sep = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
			{
				if (s[i + 1] == '\0')
					return (sep);
				i++;
			}
			sep++;
		}
		i++;
	}
	return (sep);
}

static	size_t	len_word(const char *src, size_t start, char c)
{
	size_t	i;

	i = 0;
	while (src[start] != c && src[start] != '\0')
	{
		start++;
		i++;
	}
	return (i);
}

static char	**cikl(char const *s, char c, size_t i, char **mass)
{
	size_t	word;

	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			mass[word] = ft_substr(s, i, len_word(s, i, c));
			if (mass[word] == NULL)
				jango(mass, word);
			word++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
		{
			mass[word] = NULL;
			return (mass);
		}
		i++;
	}
	mass[word] = NULL;
	return (mass);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**mass;

	i = 0;
	if (!s)
		return (NULL);
	mass = (char **)malloc((schet(s, c) + 2) * sizeof(char *));
	if (mass == NULL)
		return (NULL);
	mass[schet(s, c)] = NULL;
	while (s[i] == c && s[i] != '\0')
	{
		if (s[i + 1] == '\0')
			return (mass);
		i++;
	}
	mass = cikl(s, c, i, mass);
	return (mass);
}
