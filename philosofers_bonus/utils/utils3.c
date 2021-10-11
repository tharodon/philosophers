/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:39:44 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/19 12:39:45 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers_bonus.h"

t_philo	*lnew_el(int num, t_data *data)
{
	t_philo			*el;

	el = (t_philo *)malloc(sizeof(t_philo));
	if (!el)
		return (NULL);
	el->number = num;
	el->back = NULL;
	el->next = NULL;
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
}

void	ladd_to_list(t_philo **lst, t_philo *el)
{
	if (!el)
		return ;
	if (!*lst)
	{
		*lst = el;
		return ;
	}
	el->next = *lst;
	(*lst)->back = el;
	*lst = el;
}

void	free_all_dauther(t_philo **lst)
{
	t_philo	*tmp;
	int		count_phi;

	count_phi = (*lst)->data->count_philo;
	if (!*lst)
		return ;
	tmp = (*lst)->back;
	tmp->next = NULL;
	(*lst)->back = NULL;
	free((*lst)->data->pids);
	free((*lst)->data->sems);
	while ((*lst)->next)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
