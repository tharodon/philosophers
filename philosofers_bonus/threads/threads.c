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

#include "../philosophers_bonus.h"

void	*sub_count_eat(void *p)
{
	t_philo	*phi;

	phi = (t_philo *)p;
	sem_wait(phi->data->sems->check_eating);
	phi->data->all_eat = TRUE;
	return (NULL);
}

void	*count_eat(void *p)
{
	t_philo		*phi;
	pthread_t	thread;
	long long	curr_time;

	phi = (t_philo *)p;
	phi->data->all_eat = FALSE;
	pthread_create(&thread, NULL, sub_count_eat, phi);
	curr_time = my_get_time(0) + 100;
	if (phi->eat == phi->data->should_eat)
	{
		while (!phi->data->all_eat)
		{
			if (curr_time <= my_get_time(0))
			{
				message(phi, ALL_EAT);
			}
		}
	}
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
			usleep(900);
		}
	}
	else
	{
		while (!phi->check)
		{
			wait = my_get_time(0);
			if (wait - phi->last_eat > phi->data->time_to_die)
				message(phi, DEAD);
			usleep(900);
		}
	}
	return (NULL);
}

void	*take_forks(void *p)
{
	t_philo	*phi;

	phi = (t_philo *)p;
	sem_wait(phi->data->sems->forks);
	message(phi, TAKE_LEFT_FORK);
	sem_wait(phi->data->sems->forks);
	message(phi, TAKE_RIGHT_FORK);
	phi->check = FALSE;
	return (NULL);
}

void	take_forks_th(t_philo *phi)
{
	pthread_t	thread;
	pthread_t	thread1;
	pthread_t	eat;

	phi->check = TRUE;
	if (phi->data->args == 5 && phi->data->count_philo > 1)
	{
		pthread_create(&eat, NULL, count_eat, phi);
		pthread_detach(eat);
	}
	pthread_create(&thread, NULL, take_forks, phi);
	pthread_create(&thread1, NULL, check_dead, phi);
	while (phi->check)
		usleep(300);
}
