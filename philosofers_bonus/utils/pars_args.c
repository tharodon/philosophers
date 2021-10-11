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

#include "../philosophers_bonus.h"

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

sem_t	*sem_gen(const char *name, uint16_t value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

t_semo	*get_sem(t_data *data)
{
	t_semo	*sems;

	sems = (t_semo *)malloc(sizeof(t_semo));
	sems->dem_dead = sem_gen(SEM_DEAD, 0);
	sems->eat = sem_gen(SEM_EAT, 1);
	sems->forks = sem_gen(SEM_FORKS, data->count_philo);
	sems->print = sem_gen(SEM_PRINT, 1);
	sems->check_eating = sem_gen(SEM_ALL_EAT, data->count_philo - 1);
	return (sems);
}

void	data_record(t_data *el, int *args, int argc)
{
	el->count_philo = args[0];
	el->time_to_die = args[1];
	el->time_to_eat = args[2];
	el->time_to_sleep = args[3];
	el->args = argc;
	if (argc == 5)
		el->should_eat = args[4];
	el->all_eat = 0;
	el->is_dead = 0;
	el->sems = get_sem(el);
	el->pids = (pid_t *)malloc(sizeof(pid_t) * (el->count_philo));
}
