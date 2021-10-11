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

#include "../philosophers_bonus.h"

void	start_threads(t_philo *philo, t_data *data, int count)
{
	pid_t	pid;

	while (count--)
	{
		pid = fork();
		if (!pid)
		{
			life_philo(philo);
			exit(EXIT_SUCCESS);
		}
		data->pids[count] = pid;
		philo = philo->next;
		usleep(10);
	}
}
