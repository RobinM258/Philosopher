/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:07:30 by romartin          #+#    #+#             */
/*   Updated: 2023/07/21 10:31:10 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void ft_break(t_list *list, t_philo *philo)
{
	int	i;

	i = 0;
	//while (++i <= list->nb_philo)
		//pthread_join(philo[i].id NULL);
	i = 0;
	while (++i <list->nb_philo)
		pthread_mutex_destroy(&list->fork[i]);
	pthread_mutex_unlock(&(list->writing));
	pthread_mutex_destroy(&(list->writing));
	pthread_mutex_destroy(&list->check_meal);
}

int full_digit(char **argv, int len)
{
	int i;
	int a;

	i = 1;
	a = 0;
	while (i <= len)
	{
		a = 0;
		while (argv[i][a])
		{
			if ((argv[i][a] < '0' || argv[i][a] > '9'))
				return (1);
			a++;
		}
		i++;
	}
	return (0);
}

long long timestamp(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void ft_time_to_eat(long long time)
{
	long long past;

	past = timestamp();
	while(1)
	{
		if (timestamp() - past >= time)
			break;
		usleep(time / 10);
	}
}

void ft_print(t_philo *philo, char *str)
{
	if (philo->list->died != 1)
	{
		printf("%lli %d %s\n",(timestamp() - philo->list->start), philo->id, str);
	}
}

void init_mutex(t_list *list)
{
	int i;

	i = list->nb_philo;
	while (--i >= 0)
	{
		pthread_mutex_init(&list->fork[i], NULL);
	}
	pthread_mutex_init(&list->writing, NULL);
}

int	check_death(t_philo *ph, long long i)
{
	if (i >= ph->list->time_to_die)
		return (1);
	return(0);
}

void is_dead(t_list *list, t_philo *philo)
{
	long long	time;
	int	i;

	i = 1;
	while (list->all_eat == 0)
	{
		if (i >= list->nb_philo)
		{
			i = 1;
		}
		time = timestamp();
		if (time - philo[i].last_meal > list->time_to_die)
		{
			ft_print(philo, " died\n");
			list->died = 1;
		}
		if (philo[i].nb_meal >= list->time_to_eat)
			list->meal++;
		if (list->died == 1)
			break;
		i++;
		usleep(100);
	}
}


void eat(t_philo *phil)
{
	t_list *list;

	list = phil->list;
	pthread_mutex_lock(&list->fork[phil->left_fork]);
	pthread_mutex_lock(&(list->writing));
	ft_print(phil, " has taken a fork\n");
	pthread_mutex_unlock(&(list->writing));
	pthread_mutex_lock(&list->fork[phil->right_fork]);
	pthread_mutex_lock(&(list->writing));
	ft_print(phil, " has taken a fork\n");
	pthread_mutex_unlock(&(list->writing));
	pthread_mutex_unlock(&list->fork[phil->left_fork]);
	pthread_mutex_unlock(&list->fork[phil->right_fork]);
	pthread_mutex_lock(&list->check_meal);
	pthread_mutex_lock(&(list->writing));
	ft_print(phil, " is eating\n");
	pthread_mutex_unlock(&(list->writing));
	phil->last_meal = timestamp();
	pthread_mutex_unlock(&list->check_meal);
	ft_time_to_eat(list->time_to_eat);
	if (phil->list->time_to_eat != -1)
		phil->nb_meal++;
	pthread_mutex_unlock(&list->fork[phil->left_fork]);
	pthread_mutex_unlock(&list->fork[phil->right_fork]);
}

void time_to_sleep(t_philo *phil)
{
	long long past;

	past = timestamp();
	while(1)
	{
		if (timestamp() - past >= phil->list->time_to_sleep)
			break;
		usleep(phil->list->time_to_sleep / 10);
	}
}

void *philo_life(void *void_philo)
{
	t_philo	*phil;
	t_list	*list;

	phil = (t_philo *)void_philo;
	list = phil->list;
	if (phil->id  % 2 == 0)
		usleep(300);
	while(list->died != 1)
	{
		eat(phil);
		pthread_mutex_lock(&(phil->list->writing));
		ft_print(phil, " is sleeping\n");
		pthread_mutex_unlock(&(phil->list->writing));
		time_to_sleep(phil);
		pthread_mutex_lock(&(phil->list->writing));
		ft_print(phil, " is thinking\n");
		pthread_mutex_unlock(&(phil->list->writing));
	}
	//pthread_exit(NULL);
	return(0);
}

void init_philo(t_list *list)
{
	int i;

	i = list->nb_philo;
	while (--i >= 0)
	{
		list->philo[i].id = i + 1;
		list->philo[i].last_meal = 0;
		list->philo[i].left_fork = i;
		list->philo[i].nb_meal = 0;
		list->philo[i].right_fork = (i + 1) % list->nb_philo;
		list->philo[i].list = list;
	}
}

void create_thread(t_list *list)
{
	int i;

	i = 0;
	list->start = timestamp();
	while(i < list->nb_philo)
	{
		pthread_create(&list->philo[i].ph, NULL, philo_life, &list->philo[i]);
		i++;
	}
	is_dead(list, list->philo);
	ft_break(list, list->philo);
}

void Error(t_list *list, char **av)
{
	if (list->nb_philo == 0 || list->time_to_die == 0 || list->time_to_eat == 0 || list->time_to_sleep == 0)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	if (av[5] && list->nb_of_meal == 0)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
}

void Atribution_four(t_list *list, char **av)
{
	list->nb_philo = ft_atoi(av[1]);
	list->time_to_die = ft_atoi(av[2]);
	list->time_to_eat = ft_atoi(av[3]);
	list->time_to_sleep = ft_atoi(av[4]);
}

void Atribution_five(t_list *list, char **av)
{
	list->nb_philo = ft_atoi(av[1]);
	list->time_to_die = ft_atoi(av[2]);
	list->time_to_eat = ft_atoi(av[3]);
	list->time_to_sleep = ft_atoi(av[4]);
	list->nb_of_meal = ft_atoi(av[5]);
}

int main (int ac, char **av)
{
	t_list *list;
	int i;

	i = 0;

	list = malloc(sizeof(t_list));
	if (!list)
	{
		return (0);
	}
		if (ac == 5)
		{
			if (full_digit(av, 4) == 1)
			{
				printf("Error argument\n");
				free(list);
				return (0);
			}
			Atribution_four(list, av);
		}
		if (ac == 6)
		{
			if (full_digit(av, 5) == 1)
			{
				free(list);
				printf("Error argument\n");
				return (0);
			}
			Atribution_five(list, av);
		}
		Error(list, av);
	init_philo(list);
	init_mutex(list);
	create_thread(list);
	while (1)
		i++;
	return (0);
}
