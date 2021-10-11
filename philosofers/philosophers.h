/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:18:35 by tharodon          #+#    #+#             */
/*   Updated: 2021/08/19 13:18:36 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <stdio.h>
# define TRUE 1
# define FALSE 0
# define TAKE_LEFT_FORK 3
# define TAKE_RIGHT_FORK 4
# define THINK 5
# define EAT 6
# define ALL_EAT 7
# define SLEEP 8
# define DEAD 9

typedef struct s_data
{
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		eat;
	int					count_philo;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					should_eat;
	int					args;
	long long			base_time;
	_Bool				all_eat;
	_Bool				is_dead;
}	t_data;

typedef struct s_philosofer
{
	pthread_t			hero;
	long long			last_eat;
	struct s_philosofer	*next;
	struct s_philosofer	*back;
	int					number;
	_Bool				check;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	struct s_data		*data;
	int					eat;
}			t_philo;

long long	my_get_time(long long start);
t_philo		*lnew_el(int num, t_data *data);

void		*life_philo(void *p);
void		*check_dead(void *p);
void		*count_eat(void *p);
void		*ft_calloc(size_t n, size_t len);
void		ft_bzero(void *s, size_t n);
void		ladd_to_list(t_philo **lst, t_philo *el);
void		square_list(t_philo **lst);
void		data_record(t_data *el, int *args, int argc);
void		message(t_philo *phi, short s);
void		my_usleep(int time, t_philo *phi, short def);
void		take_forks_th(t_philo *phi);
void		check_eat(t_philo *phi);
void		free_all(t_philo **lst);
void		start_threads(t_philo *philo, t_data *data, int count);
void		message_about_not_valid(void);

char		**ft_split(char const *s, char c);
char		**ft_validate(int argc, char **argv);
char		*ft_substr(char const *s, int start, int len);

int			*pars_args(char **argv);
int			ft_atoi(const char *str);
int			ft_strlen(const char *str);
int			ft_isdigit(int c);
int			lentab(char **argv);

#endif
