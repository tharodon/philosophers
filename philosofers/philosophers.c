/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:45:40 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/15 07:53:22 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, const char **av)
{
	t_philo	*philo;
	t_data	*data;
	int		*args;
	int		count;
	char	**argv;

	argv = ft_validate(argc, (char **)av);
	if (argv == NULL)
		return (0);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	args = pars_args((char **)argv);
	data_record(data, args, lentab(argv));
	count = args[0];
	while (count)
		ladd_to_list(&philo, lnew_el(count--, data));
	square_list(&philo);
	count = args[0];
	philo->data->base_time = my_get_time(0);
	start_threads(philo, data, count);
	free_all(&philo);
	return (0);
}
