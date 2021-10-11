/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:33:06 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:33:07 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	check_eat(t_philo *phi)
{
	int				i;
	pthread_mutex_t	eat;

	i = 0;
	pthread_mutex_lock(&eat);
	while (!phi->data->is_dead && phi->eat >= phi->data->should_eat)
	{
		if (i >= phi->data->count_philo)
			phi->data->all_eat = 1;
		phi = phi->next;
		i++;
		usleep(30);
	}
}

void	*count_eat(void *p)
{
	t_philo	*phi;

	phi = (t_philo *)p;
	while (!phi->data->all_eat)
	{
		check_eat(phi);
		usleep(10);
	}
	if (phi->data->all_eat)
		message(phi, ALL_EAT);
	return (NULL);
}

void	*check_dead(void *p)
{
	t_philo		*phi;
	long long	wait;

	phi = (t_philo *)p;
	if (phi->check)
	{
		while (phi->check)
		{
			wait = my_get_time(0);
			if (wait - phi->last_eat > phi->data->time_to_die)
				message(phi, DEAD);
			usleep(100);
		}
	}
	else
	{
		while (!phi->check)
		{
			wait = my_get_time(0);
			if (wait - phi->last_eat > phi->data->time_to_die)
				message(phi, DEAD);
			usleep(100);
		}
	}
	return (NULL);
}

void	*take_forks(void *p)
{
	t_philo	*phi;

	phi = (t_philo *)p;
	if (!phi->number % 2)
	{
		pthread_mutex_lock(phi->left_fork);
		message(phi, TAKE_LEFT_FORK);
		pthread_mutex_lock(phi->right_fork);
		message(phi, TAKE_RIGHT_FORK);
	}
	else
	{
		pthread_mutex_lock(phi->right_fork);
		message(phi, TAKE_RIGHT_FORK);
		pthread_mutex_lock(phi->left_fork);
		message(phi, TAKE_LEFT_FORK);
	}
	phi->check = FALSE;
	return (NULL);
}

void	take_forks_th(t_philo *phi)
{
	pthread_t	thread;
	pthread_t	thread1;
	pthread_t	eat;

	phi->check = TRUE;
	if (phi->data->args == 5)
	{
		pthread_create(&eat, NULL, count_eat, phi);
		pthread_detach(eat);
	}
	pthread_create(&thread, NULL, take_forks, phi);
	pthread_create(&thread1, NULL, check_dead, phi);
	while (phi->check)
		usleep(100);
}
