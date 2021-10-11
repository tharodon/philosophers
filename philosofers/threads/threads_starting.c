/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_starting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:32:57 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:32:59 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	start_threads(t_philo *philo, t_data *data, int count)
{
	while (count--)
	{
		pthread_create(&philo->hero, NULL, life_philo, philo);
		philo = philo->next;
		usleep(10);
	}
	while (!data->is_dead)
		usleep(100);
	count = data->count_philo;
	while (count-- && philo->next)
	{
		pthread_detach(philo->hero);
		philo = philo->next;
	}
}
