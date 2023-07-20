/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:37:28 by robin             #+#    #+#             */
/*   Updated: 2023/07/19 18:04:51 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
	int id;
	int last_meal;
	int left_fork;
	int right_fork;
	int nb_meal;
	struct s_list *list;
	pthread_t ph;
}	t_philo;

typedef struct s_list
{
	int nb_philo;
	int time_to_sleep;
	int time_to_eat;
	int	time_to_die;
	int nb_of_meal;
	int	all_eat;
	int died;
	int meal;
	long long start;
	t_philo		philo[250];
	pthread_mutex_t		fork[250];
	pthread_mutex_t		writing;
	pthread_mutex_t		check_meal;
}	t_list;

int	ft_atoi(const char *str);
int	full_digit(char **argv, int len);
#endif