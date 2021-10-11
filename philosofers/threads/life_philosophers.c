/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:32:20 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:32:21 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ul_message(t_philo *phi, short s, long long time)
{
	if (s == TAKE_LEFT_FORK)
		printf("\033[0;35m%lldms Philosopher #%d took left fork\n", \
		time, phi->number);
	else if (s == TAKE_RIGHT_FORK)
		printf("\033[0;35m%lldms Philosopher #%d took right fork\n", \
		time, phi->number);
}

void	message(t_philo *phi, short s)
{
	long long	time;

	time = my_get_time(phi->data->base_time);
	pthread_mutex_lock(&phi->data->mutex_print);
	if (s == TAKE_LEFT_FORK || s == TAKE_RIGHT_FORK)
		ul_message(phi, s, time);
	else if (s == THINK)
		printf("\033[0;32m%lldms Philosopher #%d thinking\n", time, phi->number);
	else if (s == EAT)
		printf("\033[0;33m%lldms Philosopher #%d eating\n", time, phi->number);
	else if (s == SLEEP)
		printf("\033[0;39m%lldms Philosopher #%d sleep\n", time, phi->number);
	else if (s == DEAD || s == ALL_EAT)
	{
		if (s == DEAD)
			printf("\033[0;31m%lldms Philosopher #%d DEAD!!!\n", \
			time, phi->number);
		else
			printf("\033[0;41m%lldms All eat!\n", time);
		phi->data->is_dead = 1;
		usleep(10);
		return ;
	}
	pthread_mutex_unlock(&phi->data->mutex_print);
}

void	*life_philo(void *p)
{
	t_philo	*phi;

	phi = (t_philo *)p;
	phi->last_eat = my_get_time(0);
	while (TRUE)
	{
		message(phi, THINK);
		take_forks_th(phi);
		phi->last_eat = my_get_time(0);
		message(phi, EAT);
		my_usleep(phi->data->time_to_eat, phi, EAT);
		phi->eat++;
		pthread_mutex_unlock(phi->left_fork);
		pthread_mutex_unlock(phi->right_fork);
		message(phi, SLEEP);
		my_usleep(phi->data->time_to_sleep, phi, SLEEP);
	}
}
