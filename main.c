/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romartin <romartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:07:30 by romartin          #+#    #+#             */
/*   Updated: 2023/07/25 15:09:01 by romartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_time(t_philo *ph, long long i)
{
	if (i >= ph->list->time_to_die)
		return (1);
	return (0);
}

void	is_dead(t_list *list, t_philo *philo)
{
	long long	time;
	int			i;

	i = 0;
	while (list->all_eat != list->nb_philo)
	{
		if (i >= list->nb_philo)
			i = 0;
		time = get_time(list);
		if (time - philo[i].last_meal > list->time_to_die)
		{
			pthread_mutex_lock(&(list->die));
			ft_print(philo, " died\n");
			list->died = 1;
			pthread_mutex_unlock(&(list->die));
		}
		if (philo[i].nb_meal >= list->time_to_eat)
			list->meal++;
		if (list->died == 1)
			break ;
		i++;
		usleep(500);
	}
}

void	error(t_list *list, char **av)
{
	if (list->nb_philo <= 0 || list->time_to_die <= 0
		|| list->time_to_eat <= 0 || list->time_to_sleep <= 0)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	if (av[5] && list->nb_of_meal == 0)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

int	func(int ac, char **av, t_list *list)
{
	if (ac == 5)
	{
		if (full_digit(av, 4) == 1)
		{
			write(2, "Error\n", 6);
			free(list);
			return (0);
		}
		atribution_four(list, av);
	}
	if (ac == 6)
	{
		if (full_digit(av, 5) == 1)
		{
			free(list);
			write(2, "Error\n", 6);
			return (0);
		}
		atribution_five(list, av);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_list	*list;
	int		i;

	i = 0;
	list = malloc(sizeof(t_list));
	if (!list)
		return (0);
	if (func(ac, av, list) == 0)
		return (0);
	error(list, av);
	pthread_create(&(list->thread_time), NULL, timestamp, list);
	pthread_detach(list->thread_time);
	while (!get_time(list))
		;
	init_philo(list);
	init_mutex(list);
	create_thread(list);
	return (0);
}
