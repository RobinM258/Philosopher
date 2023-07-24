/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romartin <romartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:29:48 by romartin          #+#    #+#             */
/*   Updated: 2023/07/24 18:09:51 by romartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat2(t_philo *phil)
{
	t_list	*list;

	list = phil->list;
	ft_time_to_eat(list->time_to_eat);
	pthread_mutex_unlock(&list->fork[phil->left_fork]);
	pthread_mutex_unlock(&list->fork[phil->right_fork]);
}

void	eat(t_philo *phil)
{
	t_list	*list;

	list = phil->list;
	pthread_mutex_lock(&list->fork[phil->left_fork]);
	check_die(list);
	pthread_mutex_lock(&(list->writing));
	ft_print(phil, "has taken a fork\n");
	pthread_mutex_unlock(&(list->writing));
	pthread_mutex_lock(&list->fork[phil->right_fork]);
	check_die(list);
	pthread_mutex_lock(&(list->writing));
	ft_print(phil, "has taken a fork\n");
	pthread_mutex_unlock(&(list->writing));
	check_die(list);
	pthread_mutex_lock(&(list->writing));
	ft_print(phil, "is eating\n");
	pthread_mutex_unlock(&(list->writing));
	if (phil->list->time_to_eat != -1)
		phil->nb_meal++;
	pthread_mutex_lock(&list->check_meal);
	if (phil->nb_meal == list->nb_of_meal)
		list->all_eat++;
	phil->last_meal = timestamp();
	pthread_mutex_unlock(&list->check_meal);
	eat2(phil);
}

void	*philo_life(void *void_philo)
{
	t_philo	*phil;
	t_list	*list;

	phil = (t_philo *)void_philo;
	list = phil->list;
	if (phil->id % 2 == 0)
		usleep(300);
	while ((list->died != 1 && phil->nb_meal < list->nb_of_meal)
		|| (list->died != 1 && list->nb_of_meal == -1))
	{
		eat(phil);
		pthread_mutex_lock(&(phil->list->writing));
		ft_print(phil, "is sleeping\n");
		pthread_mutex_unlock(&(phil->list->writing));
		time_to_sleep(phil);
		pthread_mutex_lock(&(phil->list->writing));
		ft_print(phil, "is thinking\n");
		pthread_mutex_unlock(&(phil->list->writing));
	}
	return (0);
}

void	time_to_sleep(t_philo *phil)
{
	long long	past;

	past = timestamp();
	while (1)
	{
		if (timestamp() - past >= phil->list->time_to_sleep)
			break ;
		usleep(phil->list->time_to_sleep / 10);
	}
}

void	check_die(t_list *list)
{
	pthread_mutex_lock(&(list->die));
	if (list->died == 1)
		ft_break(list);
	pthread_mutex_unlock(&(list->die));
}
