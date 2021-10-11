/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:33:30 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:33:32 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

char	**re_record_argv(char **argv)
{
	int	i;
	int	str;

	i = 0;
	str = 1;
	while (argv[str])
	{
		argv[i] = argv[str];
		i++;
		str++;
	}
	argv[i] = NULL;
	return (argv);
}

int	lentab(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	check_null(char **argv, int i)
{
	int	stop;

	stop = 0;
	while (argv[i] && stop < 4)
	{
		if (argv[i][0] == '0')
			return (1);
		i++;
		stop++;
	}
	return (0);
}

int	check_digit(char **argv, int str)
{
	int	i;

	while (argv[str])
	{
		i = -1;
		while (argv[str][++i])
		{
			if (!ft_isdigit(argv[str][i]))
				return (1);
		}
		str++;
	}
	return (0);
}

char	**ft_validate(int argc, char **argv)
{
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		if ((lentab(argv) < 4 || lentab(argv) > 5) || \
		check_digit(argv, 0) || check_null(argv, 0))
		{
			message_about_not_valid();
			return (NULL);
		}
		return (argv);
	}
	else if (argc < 5 || argc > 6 || check_digit(argv, 1) || \
	check_null(argv, 1))
	{
		message_about_not_valid();
		return (NULL);
	}
	return (re_record_argv(argv));
}
