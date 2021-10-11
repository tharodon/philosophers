/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:32:31 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:32:34 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	*pars_args(char **argv)
{
	int	*str;

	str = (int *)malloc((lentab(argv) + 1) * sizeof(int));
	if (!str)
		return (NULL);
	str[0] = ft_atoi(argv[0]);
	str[1] = ft_atoi(argv[1]);
	str[2] = ft_atoi(argv[2]);
	str[3] = ft_atoi(argv[3]);
	if (lentab(argv) == 5)
	{
		str[4] = ft_atoi(argv[4]);
		str[5] = '\0';
	}
	else
		str[4] = '\0';
	return (str);
}

t_philo	*lnew_el(int num, t_data *data)
{
	t_philo			*el;

	el = (t_philo *)malloc(sizeof(t_philo));
	if (!el)
		return (NULL);
	el->number = num;
	el->back = NULL;
	el->next = NULL;
	el->right_fork = NULL;
	el->left_fork = malloc(sizeof(pthread_mutex_t));
	el->data = data;
	el->eat = 0;
	return (el);
}

void	square_list(t_philo **lst)
{
	t_philo	*start;
	t_philo	*end;

	while ((*lst)->back)
		*lst = (*lst)->back;
	start = *lst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	end = *lst;
	end->next = start;
	start->back = end;
	start->right_fork = end->left_fork;
}

void	ladd_to_list(t_philo **lst, t_philo *el)
{
	if (!el)
		return ;
	if (!*lst)
	{
		*lst = el;
		pthread_mutex_init(el->left_fork, NULL);
		return ;
	}
	el->next = *lst;
	(*lst)->back = el;
	pthread_mutex_init(el->left_fork, NULL);
	(*lst)->right_fork = el->left_fork;
	*lst = el;
}

void	data_record(t_data *el, int *args, int argc)
{
	pthread_mutex_init(&el->mutex_print, NULL);
	el->count_philo = args[0];
	el->time_to_die = args[1];
	el->time_to_eat = args[2];
	el->time_to_sleep = args[3];
	el->args = argc;
	if (argc == 5)
	{
		el->should_eat = args[4];
		pthread_mutex_init(&el->eat, NULL);
	}
	el->all_eat = 0;
	el->is_dead = 0;
}
