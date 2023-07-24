/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romartin <romartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:38:30 by romartin          #+#    #+#             */
/*   Updated: 2023/07/24 16:53:23 by romartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_list *list)
{
	int	i;

	i = 0;
	list->start = timestamp();
	while (i < list->nb_philo)
	{
		pthread_create(&list->philo[i].ph, NULL, philo_life, &list->philo[i]);
		i++;
	}
	is_dead(list, list->philo);
	ft_break(list);
}

void	init_philo(t_list *list)
{
	int	i;

	i = list->nb_philo;
	while (--i >= 0)
	{
		list->philo[i].last_meal = timestamp();
		list->philo[i].id = i + 1;
		list->philo[i].left_fork = i;
		list->philo[i].nb_meal = 0;
		list->philo[i].right_fork = (i + 1) % list->nb_philo;
		list->philo[i].list = list;
	}
}

void	atribution_four(t_list *list, char **av)
{
	list->nb_philo = ft_atoi(av[1]);
	list->time_to_die = ft_atoi(av[2]);
	list->time_to_eat = ft_atoi(av[3]);
	list->time_to_sleep = ft_atoi(av[4]);
	list->nb_of_meal = -1;
}

void	atribution_five(t_list *list, char **av)
{
	list->nb_philo = ft_atoi(av[1]);
	list->time_to_die = ft_atoi(av[2]);
	list->time_to_eat = ft_atoi(av[3]);
	list->time_to_sleep = ft_atoi(av[4]);
	list->nb_of_meal = ft_atoi(av[5]);
}

void	init_mutex(t_list *list)
{
	int	i;

	i = list->nb_philo;
	while (--i >= 0)
		pthread_mutex_init(&list->fork[i], NULL);
	pthread_mutex_init(&list->writing, NULL);
	pthread_mutex_init(&list->die, NULL);
}
