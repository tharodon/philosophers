/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:33:19 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 04:33:21 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	free_all(t_philo **lst)
{
	t_philo	*tmp;

	if (!*lst)
		return ;
	tmp = (*lst)->back;
	tmp->next = NULL;
	(*lst)->back = NULL;
	pthread_mutex_destroy(&(*lst)->data->mutex_print);
	while ((*lst)->next)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->left_fork);
		pthread_detach(tmp->hero);
		pthread_mutex_destroy((*lst)->left_fork);
		free(tmp);
	}	
}

void	my_usleep(int time, t_philo *phi, short def)
{
	time_t		begin;
	time_t		end;
	pthread_t	thread;

	begin = my_get_time(0);
	end = my_get_time(0) + time;
	if (def != EAT)
	{
		pthread_create(&thread, NULL, check_dead, phi);
		pthread_detach(thread);
	}
	while (begin < end)
	{
		usleep(100);
		begin = my_get_time(0);
	}
}

long long	my_get_time(long long start)
{
	struct timeval		tv;
	long long			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000000 + tv.tv_usec) / 1000);
	return (time - start);
}

void	message_about_not_valid(void)
{
	printf("please, enter valis value.\n");
	printf("Example: number_of_philosophers, time_to_die, time_to_eat ");
	printf("time_to_sleep, [number_of_each_philosopher_must_eat]\n");
}
